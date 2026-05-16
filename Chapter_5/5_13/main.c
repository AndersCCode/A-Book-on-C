/* Write the program tail, which prints the last n lines of its input.
By default, n is 10, let us say, but it can be changed by an optional argument, 
so that 

tail -n

prints the las n lines. The program should behave rationally no matter how
unreasonably the input or the value of n. Write the program so it makes the 
best use of available storage; lines should be stored as in the sorting 
program of Section 5.6, not in a two-dimensional array of fixed size.

gcc -Wall -Wextra -O2 -o entab main.c


/* tail - print last n lines of input; default n = 10 */
/* gcc -Wall -Wextra -O2 -o tail tail.c */

// ./tail < input.txt
// ./tail -3 < input.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES   10000
#define MAXLEN     1000
#define MAXSTORAGE 1000000

char *lineptr[MAXLINES];
char linebuf[MAXSTORAGE];

int get_line(char *s, int lim)
{
    int c;
    char *start = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return (int)(s - start);
}

/* Store lines in linebuf; pointers in lineptr. Return count or -1 on overflow. */
int readlines(char *lineptr[], int maxlines, char *linebuf, int maxstorage)
{
    int len, nlines;
    char *p, *end, line[MAXLEN];

    nlines = 0;
    p = linebuf;
    end = linebuf + maxstorage;

    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || p + len + 1 > end)
            return -1;
        if (len > 0 && line[len - 1] == '\n')
            line[--len] = '\0';
        strcpy(p, line);
        lineptr[nlines++] = p;
        p += len + 1;
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* Parse optional "-n" (e.g. -10). Default 10. */
int parse_n(int argc, char *argv[])
{
    int n;

    if (argc <= 1)
        return 10;
    if (argv[1][0] != '-' || argv[1][1] == '\0') {
        fprintf(stderr, "usage: tail [-n]\n");
        exit(1);
    }
    n = atoi(argv[1] + 1);
    return n < 0 ? 0 : n;
}

int main(int argc, char *argv[])
{
    int nlines, n, first;

    n = parse_n(argc, argv);

    if ((nlines = readlines(lineptr, MAXLINES, linebuf, MAXSTORAGE)) < 0) {
        fprintf(stderr, "tail: input too large\n");
        return 1;
    }

    if (n == 0)
        return 0;

    if (n > nlines)
        n = nlines;
    first = nlines - n;

    writelines(lineptr + first, n);
    return 0;
}