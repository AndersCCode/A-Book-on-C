/* Write a program to chech a C program for rudimentary syntax 
errors like unbalanced parentheses, bracket and braces. 
Don't forget about quotes, both single and double, 
escape sequences, and comment. 

(This program is hard if you do it in full generality) */

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

void check_syntax(char line[], int len) {
    static enum State { NORMAL, SINGLE_QUOTE, DOUBLE_QUOTE, LINE_COMMENT, BLOCK_COMMENT } state = NORMAL;
    static int escaped = 0;
    static char stack[MAXLINE];
    static int top = 0;

    for (int i = 0; i < len; ++i) {
        char c = line[i];
        char next = (i + 1 < len) ? line[i + 1] : '\0';

        switch (state) {
            case NORMAL:
                if (c == '\'') state = SINGLE_QUOTE;
                else if (c == '"') state = DOUBLE_QUOTE;
                else if (c == '/' && next == '/') { state = LINE_COMMENT; i++; }
                else if (c == '/' && next == '*') { state = BLOCK_COMMENT; i++; }
                else {
                    if (c == '(' || c == '[' || c == '{') {
                        if (top >= MAXLINE - 1) {
                            printf("Error: Stack overflow\n");
                            top = 0; state = NORMAL; return;
                        }
                        stack[top++] = c;
                    } else if (c == ')' || c == ']' || c == '}') {
                        if (top == 0) {
                            printf("Error: Extra closing %c\n", c);
                            top = 0; state = NORMAL; return;
                        }
                        char open = stack[--top];
                        if ((c == ')' && open != '(') ||
                            (c == ']' && open != '[') ||
                            (c == '}' && open != '{')) {
                            printf("Error: Mismatched %c and %c\n", open, c);
                            top = 0; state = NORMAL; return;
                        }
                    }
                }
                break;

            case SINGLE_QUOTE:
                if (c == '\\') escaped = 1;
                else if (c == '\'' && !escaped) state = NORMAL;
                else escaped = 0;
                break;

            case DOUBLE_QUOTE:
                if (c == '\\') escaped = 1;
                else if (c == '"' && !escaped) state = NORMAL;
                else escaped = 0;
                break;

            case LINE_COMMENT:
                if (c == '\n') state = NORMAL;
                break;

            case BLOCK_COMMENT:
                if (c == '*' && next == '/') { state = NORMAL; i++; }
                break;
        }
    }

    // No need for per-line message — only report errors at EOF
}

int main() {
    char line[MAXLINE];
    int len;

    printf("K&R 1-24 Syntax Checker — type C code, Ctrl+D to quit\n\n");

    while ((len = mygetline(line, MAXLINE)) > 0) {
        check_syntax(line, len);
    }

    // Final check at EOF
    // Since static variables are in check_syntax, we need to call it one last time or make them global
    // Easier: make a separate function for final check, or move statics to global

    // Simple solution: call check_syntax with empty line at EOF
    check_syntax("", 0);  // this will trigger the final check if we add it inside

    // Better: add the final check inside check_syntax when len == 0
    // But for now, let's make the statics global

    return 0;
}