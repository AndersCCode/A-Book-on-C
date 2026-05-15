/* Modify the programs entab and detab (written as exercises in Chapter 1) 
to accept a list of tab stops as arguments. Use the default tab settings 
if there are no arguments. 

entab - replace strings of blanks by the minimum number of tabs and blanks
to achieve the same spacing. 

i.e. 9 spaces should be translated to 1 tab and 1 space */

/* entab: replace strings of blanks by the minimum number of tabs + blanks
  to achieve the same spacing, using a list of tab stops.

gcc -Wall -Wextra -O2 -o entab main.c

8 spaces
echo "        " | ./entab -4 +8 | od -An -t x1
Exptected output: 09 20 20 20 0a 

*/

#include <stdio.h>
#include <stdlib.h>

static int nextstop(int col, int m, int n) {
    if (col < m) return m;
    return m + (((col - m) / n) + 1) * n;   // Number of columns to get to the next tab stops (see personal notes for further details)
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: entab -m +n\n");
        return 1;
    }

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);

    if (m >= 0 || n <= 0) {
        fprintf(stderr, "Usage: entab -m +n  (m>0, n>0)\n");
        return 1;
    }
    m = -m;

    int c, col = 1;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            int nspaces = 1;
            while ((c = getchar()) == ' ')  // Add the rest of the spaces
                nspaces++;

            while (nspaces > 0) {
                int target = nextstop(col, m, n);    // Get the next tab stop 
                int need = target - col;            // Number of spaces til the next tab stop (from col)

                if (nspaces >= need) {      // Replace spaces with tabs 
                    putchar('\t');
                    col = target;
                    nspaces -= need;
                } else {
                    while (nspaces-- > 0) {
                        putchar(' ');
                        col++;
                    }
                }
            }

            /* c is the first non-space after the run */
            if (c == EOF)
                break;
            /* fall through to handle c as a normal character */
        }

        putchar(c);
        if (c == '\n')
            col = 1;
        else
            col++;
    }

    return 0;
}
