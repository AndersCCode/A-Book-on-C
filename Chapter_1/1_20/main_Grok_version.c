/* Write a program detab that replaces tabs in the input with the proper number of blanks 
to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. 
Should n be a variable or a symbolic parameter ? 
(parameter is probably loose wording, it should be constant) */

/* n should be a symbolic constant (#define Tabstop 4) */

#include <stdio.h>

#define TABSTOP 4   /* tab stops every TABSTOP columns; use 4 or 8 depending on your editor */

int main(void)
{
    int c, column = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            do {
                putchar(' ');
                ++column;
            } while (column % TABSTOP != 0);
        } else if (c == '\n') {
            putchar('\n');
            column = 0;
        } else {
            putchar(c);
            ++column;
        }
    }
    return 0;
}