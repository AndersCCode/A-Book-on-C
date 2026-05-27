/* Add the option -f to fold upper and lower case together, so that case distinctions are not made
during sorting; for example, a and A compare equal.

gcc -Wall -Wextra -O2 -o sort main.c

printf '%s\n' zebra apple 42 7 banana | ./sort          # lexicographic
printf '%s\n' zebra apple 42 7 banana | ./sort -r       # reverse lexicographic
printf '%s\n' zebra apple 42 7 banana | ./sort -n       # numeric
printf '%s\n' zebra apple 42 7 banana | ./sort -n -r    # numeric, decreasing

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES   5000
#define MAXLEN     1000
#define MAXSTORAGE 1000000

char *lineptr[MAXLINES];
char linebuf[MAXSTORAGE];

int numeric = 0;
int reverse = 0;
int fold = 0;

int numcmp(const char *s1, const char *s2)
{
    double v1 = atof(s1);
    double v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* strcmp or numcmp, then apply -r */
int mycomp(const char *s1, const char *s2)
{
    int r = 0;

    if (numeric) {
        r = numcmp(s1, s2);
    } 
    else if (fold) {
        r = strcasecmp(s1, s2);
    }
    else {
        r = strcmp(s1, s2);
    } 

    return reverse ? -r : r; 
}

void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int get_line(char *s, int lim)
{
    int c = 0;
    char *start = s;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return (int)(s - start);
}

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, *end, line[MAXLEN];

    nlines = 0;
    p = linebuf;
    end = linebuf + MAXSTORAGE;
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

/* Renamed: stdlib already has qsort() */
void mysort(void *v[], int left, int right,
            int (*comp)(const char *, const char *))    // Call the compare function on these two elements
{
    int i, last;

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    mysort(v, left, last - 1, comp);
    mysort(v, last + 1, right, comp);
}

int main(int argc, char *argv[])
{
    int nlines;
    int i;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0)
            numeric = 1;
        else if (strcmp(argv[i], "-r") == 0)
            reverse = 1;
        else if (strcmp(argv[i], "-f") == 0)
            fold = 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        mysort((void **)lineptr, 0, nlines - 1, mycomp);  
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input is too big to sort\n");
        return 1;
    }
}