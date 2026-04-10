/* Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing.
Good possibilities include getline (Chapter 1 and 4), atoi, itoa, and their variants (Chapter 2, 3 and 4), 
reverse (Chapter 3), and strindex and getop (Chapter 4). */

#include <stdio.h>

#define MAXLINE 1000

/* Read a line into s, return length */
int a_getline(char *s, int lim) 
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

/* Copy 'from' into 'to'; assume to is big enough */
void copy(char *to, const char *from) 
{
    while ((*to++ = *from++) != '\0')
        ;      
}

/* Print longest input line */
int main(void) {

    int len;                    // Current line length
    int max = 0;                // Maximum length so far
    char line[MAXLINE];         // Current input line
    char longest[MAXLINE];      // Longest line saved here

    while ((len = a_getline(line, MAXLINE)) > 1)
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    
    if (max > 0)            // There was a line
        printf("Longest line: %s\n", longest);
    
    return 0;
}