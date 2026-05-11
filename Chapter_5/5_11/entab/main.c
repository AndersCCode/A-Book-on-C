/* Modify the programs entab and detab (written as exercises in Chapter 1) 
to accept a list of tab stops as arguments. Use the default tab settings 
if there are no arguments. 

entab - replace strings of blanks by the minimum number of tabs and blanks
to achieve the same spacing. 

i.e. 9 spaces should be translated to 1 tab and 1 space */

/* entab: replace strings of blanks by the minimum number of tabs + blanks
 * to achieve the same spacing, using a list of tab stops.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXSTOPS 1000
#define TABINC   8

// If I'm currently in column col, what column will a tab take me to?
static int nextstop(int col, const int *stops, int nstops) {
    for (int i = 0; i < nstops; i++)
        if (stops[i] > col) return stops[i];
    return col + (TABINC - (col % TABINC));
}

int main(int argc, char *argv[]) {
    int stops[MAXSTOPS];
    int nstops = 0;

    for (int i = 1; i < argc && nstops < MAXSTOPS; i++) {
        int v = atoi(argv[i]);
        if (v > 0) stops[nstops++] = v;
    }

    int c, col = 1;
    int blanks = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            blanks++;
            continue;
        }

        /* flush pending blanks */
        while (blanks > 0) {
            int ns = nextstop(col, stops, nstops);
            int tostop = ns - col;          /* spaces needed to reach next stop */
            if (tostop > 0 && blanks >= tostop) {
                putchar('\t');
                blanks -= tostop;
                col = ns;
            } else {
                putchar(' ');
                blanks--;
                col++;
            }
        }

        putchar(c);
        if (c == '\n') col = 1;
        else if (c == '\t') col = nextstop(col, stops, nstops);
        else col++;
    }

    while (blanks-- > 0) putchar(' ');
    return 0;
}