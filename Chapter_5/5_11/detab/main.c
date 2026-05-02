/* detab - replace tabs with proper spaces, accepting tab stops as arguments */
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TABSTOP 4
#define MAX_STOPS 10

int main(int argc, char *argv[])
{
    int c, column = 0;
    int tabstops[MAX_STOPS];
    int n_tabstops = 0;

    // Read tab stops from command-line arguments 
    for (int i = 1; i < argc && n_tabstops < MAX_STOPS; i++) {
        tabstops[n_tabstops++] = atoi(argv[i]);
    }

    // Use default if no arguments given 
    if (n_tabstops == 0) {
        tabstops[0] = DEFAULT_TABSTOP;
        n_tabstops = 1;
    }

    // Print ruler
    int max_col = 60;

    // Line 1: Tab stop markers 
    for (int col = 0; col <= max_col; col++) {
        int is_stop = 0;
        for (int i = 0; i < n_tabstops; i++) {
            if (col == tabstops[i]) {
                is_stop = 1;
                break;
            }
        }
        putchar(is_stop ? '|' : '-');
    }
    putchar('\n');

    // Line 2: Column numbers 
    for (int col = 0; col <= max_col; col += 5) {
        printf("%-5d", col);
    }
    printf("\n\n");

    // Main detab processing
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            /* Find next tab stop after current column */
            int next_stop = 0;
            for (int i = 0; i < n_tabstops; i++) {
                if (column < tabstops[i]) {
                    next_stop = tabstops[i];
                    break;
                }
            }
            if (next_stop == 0) {
                next_stop = column + DEFAULT_TABSTOP;   /* fallback */
            }

            // Output spaces 
            for (int i = 0; i < (next_stop - column); i++) {
                putchar(' ');
            }
            column = next_stop;
        }
        else if (c == '\n') {
            putchar('\n');
            column = 0;
        }
        else {
            putchar(c);
            column++;
        }
    }

    return 0;
}
