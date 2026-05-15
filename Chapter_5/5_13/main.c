/* Write the program tail, which prints the last n lines of its input.
By default, n is 10, let us say, but it can be changed by an optional argument, 
so that 

tail -n

prints the las n lines. The program should behave rationally no matter how
unreasonably the input or the value of n. Write the program so it makes the 
best use of available storage; lines should be stored as in the sorting 
program of Section 5.6, not in a two-dimensional array of fixed size.

gcc -Wall -Wextra -O2 -o entab main.c

*/

#include <stdio.h>
#include <stdlib.h>
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
    
    int c = 0;
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
/*void qsort(char *v[], int left, int right) 
{
    int i, last;

    // Do nothting if arrary contains fewer than two elements
    if (left >= right)
        return;

     // Move partition element to v[0]
    swap(v, left, (left + right)/2);
    last = left;

    for (i = left+1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }
    
        swap(v, left, last);        // restore partition element
        qsort(v, left, last-1);
        qsort(v, last+1, right);
}*/

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

int main(int argc, char *argv[]) {
    int nlines;         // number of input lines read
    int nlines_to_write = 0;

    clock_t start, end;
    double cpu_time_used;

    start = clock();    // start timing

    if (argc == 1) {
        fprintf(stderr, "Using default value for n which is 10.\n");
        nlines_to_write = 10; 
    } 
    else if (argc == 2) {
        nlines_to_write = atoi(argv[2]);
    } 

    if ((nlines = readlines(lineptr, linebuf, MAXLINES, MAXSTORAGE)) >= 0) {
        // qsort(lineptr, 0, nlines - 1);    
        //printf("\nSorted lines:\n");
        writelines(lineptr, nlines_to_write);

        end = clock();
        cpu_time_used = ((double)(end - start) / CLOCKS_PER_SEC);

        printf("\nTime taken: %.4f seconds\n", cpu_time_used);

        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    } 
}