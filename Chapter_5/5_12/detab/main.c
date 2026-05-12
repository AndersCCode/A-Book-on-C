/* Modify the programs entab and detab (written as exercises in Chapter 1) 
to accept a list of tab stops as arguments. Use the default tab settings 
if there are no arguments.

detab - replace tabs with proper spaces, accepting tab stops (positions) as arguments 

gcc -Wall -Wextra -O2 -o detab main.c

printf '\tX\n' | ./detab 4 10 20 | od -An -t x1
Exptected output: 20 20 20 58 0a
space space space X \n

printf '\tX\tA\n' | ./detab 4 10 20 | od -An -t x1
Exptected output: 20 20 20 58 20 20 20 20 20 41 0a
space space space X space space space space space A \n

printf '\tX\tA\tB\n' | ./detab 4 10 20 | od -An -t x1
Exptected output: 20 20 20 58 20 20 20 20 20 41 20 20 20 20 20 20 20 20 20 42 0a
space space space X space space space space space A space space space space space space space space space B \n

printf '\tX\n' | ./detab | od -An -t x1
Exptected output: 20 20 20 20 20 20 20 58 0a
space space space space space space space X \n

printf '\tX\tA\n' | ./detab 4 | od -An -t x1
Exptected output: 20 20 20 58 20 20 20 41 0a
space space space X space space space A \n

*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSTOPS 1000
#define TABINC   8

static int nextstop(int col, const int *stops, int nstops) {
    for (int i = 0; i < nstops; i++)
        if (stops[i] > col) return stops[i];
    return col + (TABINC - (col % TABINC));
}

int main(int argc, char *argv[]) {
    int stops[MAXSTOPS];
    int nstops = 0;

    /* Parse tab stops as increasing column numbers (0-based or 1-based?) */
    /* Here: treat argv values as 1-based columns (more natural), convert to 0-based. */
    for (int i = 1; i < argc && nstops < MAXSTOPS; i++) {

        int v = atoi(argv[i]);  // Read argument
        
        if (v > 0) stops[nstops++] = v; // Only valid characters
    }

    int c, col = 1;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int ns = nextstop(col, stops, nstops);
            while (col < ns) {      // Add spaces until next tab stop is reached
                putchar(' ');
                col++;
            }
        } else {    // Print character
            putchar(c);
            if (c == '\n') col = 1;
            else col++;
        }
    }
    return 0;
}

