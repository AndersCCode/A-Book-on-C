/* Write a program to "fold" long input lines into two or more 
shorter lines after the last non-blank charachter that occurs 
before the n-th column of input. Make sure your program does 
something intelligent with very long lines, and if there are 
no blanks or tabs before the specified column. */

#include <stdio.h>

#define MAXLINE 1000
#define FOLD 60

int mygetline(char s[], int lim) {
    int c, i = 0;
    while (i < lim-1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n') s[i++] = '\n';
    s[i] = '\0';
    return i;
}

void fold(char line[], int len) {
    char out[MAXLINE];
    int out_pos = 0, col = 0, last_blank = 0;

    for (int i = 0; i < len; ++i) {
        out[out_pos++] = line[i];
        col++;

        if (line[i] == ' ' || line[i] == '\t')
            last_blank = out_pos;

        if (col == FOLD) {
            if (last_blank > 0) {
                out[last_blank - 1] = '\n';
                col = out_pos - last_blank;
                last_blank = 0;
            } else {
                out[out_pos++] = '\n';
                col = 0;
            }
        }
    }
    for (int i = 0; i < out_pos; ++i)
        putchar(out[i]);
}

int main() {
    char line[MAXLINE];
    int len;
    while ((len = mygetline(line, MAXLINE)) > 0)
        fold(line, len);
    return 0;
}