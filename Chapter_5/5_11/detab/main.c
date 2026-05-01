/*  Modify the programs entab and detab (written as exercises in Chapter 1) to accept 
a list of tab stops as arguments. Use the default tab settings if there are no arguments. 

This is the detab program */

#include <stdio.h>

#define TABSTOP 4   // Tab stops every TABSTOP columnns

int main(int argc, char *argv[]) {

    int c, column = 0;   // current position on the line
    int tabstops[100];
    int n_tabstops = 0;

    // if no arguments, use default
    if (argc == 1) {
            printf("Usage: ./entab [Tabstop1][Tabstop2]...[tabstopn]\n", argv[0]);
            return 1;
    }


    if (argc == 1) {
            printf("Usage: ./entab [Tabstop1][Tabstop2]...[tabstopn]\n", argv[0]);
            return 1;
    }


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


