/* Write a program to remove trailing blanks and tabs from each
line of input, and to delete entirely blank lines. */

#include <stdio.h>

#define MAXLINE 1000

int mygetline(char s[], int lim) {
    int c, i = 0;
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n') s[i++] = '\n';
    s[i] = '\0';
    return i;
}

void remove_trailing_blanks(char s[], int len) {
    int i = len - 2;  // skip the final '\n' and '\0'

    // Remove trailing spaces and tabs
    while (i >= 0 && (s[i] == ' ' || s[i] == '\t'))
        i--;

    // If the line is not entirely blank, print it
    if (i >= 0) {
        s[i + 1] = '\n';   // restore the newline
        s[i + 2] = '\0';
        printf("%s", s);
    }
    // else: entirely blank line → deleted
}

int main() {
    char line[MAXLINE];
    int len;

    while ((len = mygetline(line, MAXLINE)) > 0) {
        remove_trailing_blanks(line, len);
    }
    return 0;
}