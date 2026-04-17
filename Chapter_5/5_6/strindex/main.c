/* Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing.
Good possibilities include getline (Chapter 1 and 4), atoi, itoa, and their variants (Chapter 2, 3 and 4), 
reverse (Chapter 3), and strindex and getop (Chapter 4). */

#include <stdio.h>

#define MAXLINE 1000

/* get line into s, return length */
int a_getline(char *s, int lim)
{
    int c;
    char *start = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') 
        *s++ = c;
    
    if (c == '\n')
        *s++ = c;

    *s = '\0';

    return s - start;
}

/* return index of t in s, -1 if none */
int strindex(const char *s, const char *t)
{
    if (*t == '\0')         // empty pattern always match at position 0
        return 0;

    const char *start = s;

    while (*s != '\0') {
        const char *p = s;
        const char *q = t;

        while (*p != '\0' && *q != '\0' && *p == *q){
            p++;
            q++;
        }

        if (*q == '\0')             // found full match
            return s - start;

        s++;                        // try next position in s (line)
    }
    return -1;
}

int main(void) 
{
    char line[MAXLINE];
    char pattern[] = "abc";
    int found = 0;

    while (a_getline(line, MAXLINE) > 0) {
        if (strindex(line, pattern) >= 0) {
            printf("%s", line);
            found++;
        }
        //else printf("Not found\n");
    }

    return found; 
}