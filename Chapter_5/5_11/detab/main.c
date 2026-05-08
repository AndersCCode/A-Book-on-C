/* Modify the programs entab and detab (written as exercises in Chapter 1) 
to accept a list of tab stops as arguments. Use the default tab settings 
if there are no arguments.

detab - replace tabs with proper spaces, accepting tab stops (positions) as arguments */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE    1000
#define DEFAULT_TAB 8

// ttt

/* detab: replace tabs with the proper number of spaces */
void detab(int tabstop)
{
    int c, pos = 0;        // pos = current column

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            /* output enough spaces to reach next tab stop */
            int spaces = tabstop - (pos % tabstop);
            if (spaces == 0) spaces = tabstop;   // if already on tab stop

            for (int i = 0; i < spaces; ++i) {
                putchar(' ');
                ++pos;
            }
        }
        else if (c == '\n') {
            putchar('\n');
            pos = 0;
        }
        else {
            putchar(c);
            ++pos;
        }
    }
}

int main(int argc, char *argv[])
{
    int tabstop = DEFAULT_TAB;

    if (argc > 1) {
        tabstop = atoi(argv[1]);
        if (tabstop <= 0)
            tabstop = DEFAULT_TAB;
    }

    detab(tabstop);
    return 0;
}