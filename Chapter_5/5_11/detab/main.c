/*  Modify the programs entab and detab (written as exercises in Chapter 1) to accept 
a list of tab stops as arguments. Use the default tab settings if there are no arguments. 

This is the detab program (remove tabs from input and ajust text to tab stops) */

#include <stdio.h>
#include <stdlib.h>

#define TABSTOP 4   // Tab stops every TABSTOP columnns

int main(int argc, char *argv[]) {

    int c, column = 0;      // current position on the line
    int tabstops[100];      // array to hold the tab stop positions
    int n_tabstops = 0;     // count for how many tab stops we have


    for (int i = 1; i < argc; i++) {
            tabstops[n_tabstops++] = atoi(argv[i]);   // convert the argument to number                    
        }

    // if no arguments is given, use default
    if (n_tabstops == 0) {
        tabstops[0] = TABSTOP;
        n_tabstops = 1;
        printf("Tab stops set to %d\n", TABSTOP);
    }

    while ((c = getchar()) != EOF) {
        if (c == '\t') {

            // Find the next tab stop after current column
            int next_stop = 0;

            for (int i = 0; i < n_tabstops; i++) {
                if (column < tabstops[i]) {
                    next_stop = tabstops[i];
                    break;
                }
            }

            // If no future tab stop found, continue with default spacing
            if (next_stop == 0) {
                next_stop = column + TABSTOP;
            } 

            int spaces = next_stop - column;

            for (int i = 0; i < spaces; i++) {
                putchar(' ');
            }
            column += spaces;

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


