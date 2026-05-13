/* Modify the programs entab and detab (written as exercises in Chapter 1) 
to accept a list of tab stops as arguments. Use the default tab settings 
if there are no arguments.

detab - replace tabs with proper spaces, accepting tab stops (positions) as arguments 

gcc -Wall -Wextra -O2 -o detab main.c

printf '\tX\n' | ./detab -4 +8 | od -An -t x1
Exptected output: 20 20 20 58 0a

printf '\tX\t\A\n' | ./detab -4 +8 | od -An -t x1
Exptected output:  20 20 20 58 20 20 20 20 20 20 20 41 0a

*/

#include <stdio.h>
#include <stdlib.h>

static int nextstop(int col, int m, int n) {
    if (col < m) return m;
    return m + (((col - m) / n) + 1) * n; // Number of columns to get to the next tab stops (see personal notes for further details)
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: detab -m +n where m = start position and n = tab stop interval\n");
        return 1;
    }

    int m = atoi(argv[1]);  // expects -m
    int n = atoi(argv[2]);  // expects +n

    if (m >= 0 || n <= 0) {
        fprintf(stderr, "Usage: detab -m +n  (m>0, n>0)\n");
        return 1;
    }

    m = -m;                 // convert -m to positive m

    int c, col = 1;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int ns = nextstop(col, m, n);
            while (col < ns) {
                putchar(' ');
                col++;
            }
        } else {
            putchar(c);
            if (c == '\n') col = 1;
            else col++;
        }
    }
    return 0;
}
