/* Write a program to remove all comments from a C program. 
Don't forget to handle quoted strings and character constants 
properly. C comments do not nest. */

#include <stdio.h>

#define MAXLINE 1000

int mygetline(char s[], int lim) {
    int c, i = 0;
    while (i < lim-1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n') s[i++] = '\n';
    s[i] = '\0';
    return i;
}

void remove_comments(char line[], int len) {
    static enum { NORMAL, LINE_COMMENT, BLOCK_COMMENT, SINGLE_QUOTE, DOUBLE_QUOTE } state = NORMAL;
    static int in_quote_char = 0;

    for (int i = 0; i < len; ++i) {
        char c = line[i];
        char next = (i + 1 < len) ? line[i+1] : '\0';

        switch (state) {
            case NORMAL:
                if (c == '\'') {
                    putchar(c);
                    state = SINGLE_QUOTE;
                } else if (c == '"') {
                    putchar(c);
                    state = DOUBLE_QUOTE;
                } else if (c == '/' && next == '/') {
                    state = LINE_COMMENT;
                    i++;
                } else if (c == '/' && next == '*') {
                    state = BLOCK_COMMENT;
                    i++;
                } else {
                    putchar(c);
                }
                break;

            case SINGLE_QUOTE:
                putchar(c);
                if (c == '\\') in_quote_char = 1;
                else if (c == '\'' && !in_quote_char) state = NORMAL;
                else in_quote_char = 0;
                break;

            case DOUBLE_QUOTE:
                putchar(c);
                if (c == '\\') in_quote_char = 1;
                else if (c == '"' && !in_quote_char) state = NORMAL;
                else in_quote_char = 0;
                break;

            case LINE_COMMENT:
                if (c == '\n') { putchar('\n'); state = NORMAL; }
                break;

            case BLOCK_COMMENT:
                if (c == '*' && next == '/') {
                    state = NORMAL;
                    i++;
                }
                break;
        }
    }
}

int main() {
    char line[MAXLINE];
    int len;
    printf("C comment remover — Ctrl+D to quit\n\n");
    while ((len = mygetline(line, MAXLINE)) > 0)
        remove_comments(line, len);
    return 0;
}