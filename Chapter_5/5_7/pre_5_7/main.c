/* Rewrite readliness to store lines in an array supplied by main 
rather thatn calling alloc to maintain storage. 
How much faster is the program ? 

gcc main.c -o main && ./main < big_input.txt

Result: 1000 lines 0.0014 seconds
Result: 3000 lines 0.0039 seconds

*/

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXLEN 10000
#define MAXLINES 10000
#define ALLOCSIZE 1000000            // size of available space 

char *lineptr[MAXLINES];            

static char allocbuf[ALLOCSIZE];    // storage for alloc
static char *allocp = allocbuf;     // next free position

/* return pointer to n characters */
char *alloc(int n) 
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {   // it fits
        allocp += n;
        return allocp - n;      // old p
    } else                      // not enough room
        return 0;
}

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
int readlines(char *lineptr[], int maxlines) 
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;

    while ((len = get_line(line, MAXLEN)) > 0) {
        
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0';         // delete newline
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
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

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1);
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