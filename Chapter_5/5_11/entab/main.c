/* Modify the programs entab and detab (written as exercises in Chapter 1) 
to accept a list of tab stops as arguments. Use the default tab settings 
if there are no arguments. 

entab - replace strings of blanks by the minimum number of tabs and blanks
to achieve the same spacing. */

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

void entab(char s[], int len) {
    char buffer[MAXLINE];
    int i, j = 0, spaces = 0;

    for (i = 0; i < len; ++i) {
        if (s[i] == ' ') {
            ++spaces;
        } else {
            while (spaces >= TABSTOP) {
                buffer[j++] = '\t';
                spaces -= TABSTOP;
            }
            while (spaces > 0) {
                buffer[j++] = ' ';
                --spaces;
            }
            buffer[j++] = s[i];
        }
    }
    // trailing spaces
    while (spaces >= TABSTOP) { buffer[j++] = '\t'; spaces -= TABSTOP; }
    while (spaces > 0)        { buffer[j++] = ' '; --spaces; }

    buffer[j] = '\0';
    printf("%s", buffer);
}

int main() {
    char line[MAXLINE];
    int len;
    while ((len = mygetline(line, MAXLINE)) > 0)
        entab(line, len);
    return 0;
}