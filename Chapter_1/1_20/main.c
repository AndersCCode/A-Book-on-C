/* Write a program detab that replaces tabs in the input with the proper number of blanks 
to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. 
Should n be a variable or a symbolic parameter ? 
(parameter is probably loose wording, it should be constant) 

replace tabs with spaces*/

/* n should be a symbolic constant (#define Tabstop 4) */

#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8

int mygetline(char s[], int lim) {
    int c, i = 0;
    while (i < lim-1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n') s[i++] = '\n';
    s[i] = '\0';
    return i;
}

void detab(char s[], int len) {
    char buffer[MAXLINE];
    int i, j = 0, col = 0;

    for (i = 0; i < len; ++i) {
        if (s[i] == '\t') {
            int spaces = TABSTOP - (col % TABSTOP);
            while (spaces-- > 0) {
                buffer[j++] = ' ';
                col++;
            }
        } else {
            buffer[j++] = s[i];
            col++;
            if (s[i] == '\n') col = 0;
        }
    }
    buffer[j] = '\0';
    printf("%s", buffer);
}

int main() {
    char line[MAXLINE];
    int len;
    while ((len = mygetline(line, MAXLINE)) > 0)
        detab(line, len);
    return 0;
}