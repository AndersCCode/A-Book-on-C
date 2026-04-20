/* Rewrite readliness to store lines in an array supplied by main 
rather thatn calling alloc to maintain storage. 
How much faster is the program ? 

# Generate 1000 lines for testing
for i in {1..1000}; do echo "This is line number $i with some text to make it longer"; done > big_input.txt

gcc main.c -o main && ./main < big_input.txt

Result: 1000 lines in 0.0010 seconds

Alloc version = 0.0014 seconds
Array version = 0.0010 seconds
----------------------------------
Difference = 0.0004 seconds (29%)

Result: 3000 lines in 0.0035 seconds

Alloc version = 0.0039 seconds
Array version = 0.0035 seconds
----------------------------------
Difference = 0.0004 seconds (29%)

*/

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXLINES 10000       // max number of lines to be sorted
#define MAXLEN 10000         // max length of any input line
#define MAXSTORAGE 1000000    // size of the storage array

char *lineptr[MAXLINES];    // pointers to the lines 
char linebuf[MAXSTORAGE];   // array supplied by main (differs from pre-version that uses malloc)

/* Read a line into s, return length */
int get_line(char *s, int lim) 
{
    
    int c;
    char *start = s;

    // Read characters to s as long as we haven't reached limit, EOF (CTRL - D) or a newline
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;

    if (c == '\n')
        *s++ = c;

    *s = '\0';

    return s - start;
}

void swap(char *v[], int i, int j) 
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* sort v[left]..v[right] into increasing order */
void qsort(char *v[], int left, int right) 
{
    int i, last;

    // Do nothting if arrary contains fewer than two elements
    if (left >= right)
        return;

     // Move partition element to v[0]
    swap(v, left, (left + right)/2);
    last = left;

    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    
        swap(v, left, last);        // restore partition element
        qsort(v, left, last-1);
        qsort(v, last+1, right);
}

/* read input lines */
int readlines(char *lineptr[], char *linebuf, int maxlines, int maxstorage) 
{
    int len, nlines = 0;
    char *p = linebuf;              // next free position in linebuf
    char line[MAXLEN];
    
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || p + len > linebuf + maxstorage)
            return -1;
        
        line[len-1] = '\0';         // delete newline
        strcpy(p, line);            // copy the line into the array (buffer)
        lineptr[nlines++] = p;      // store pointer to this line
        p += len;                   // move forward in the array (buffer)
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

int main(void) 
{
    int nlines;         // number of input lines read

    clock_t start, end;
    double cpu_time_used;

    start = clock();    // start timing

    if ((nlines = readlines(lineptr, linebuf, MAXLINES, MAXSTORAGE)) >= 0) {
        qsort(lineptr, 0, nlines - 1);    
        printf("\nSorted lines:\n");
        writelines(lineptr, nlines);

        end = clock();
        cpu_time_used = ((double)(end - start) / CLOCKS_PER_SEC);

        printf("\nTime taken: %.4f seconds\n", cpu_time_used);

        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    } 
}