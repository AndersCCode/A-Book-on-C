/* Modify the programs entab and detab (written as exercises in Chapter 1) 
to accept a list of tab stops as arguments. Use the default tab settings 
if there are no arguments. 

entab - replace strings of blanks by the minimum number of tabs and blanks
to achieve the same spacing. 

i.e. 9 spaces should be translated to 1 tab and 1 space */

/* entab: replace strings of blanks by the minimum number of tabs + blanks
  to achieve the same spacing, using a list of tab stops.

gcc -Wall -Wextra -O2 -o entab main.c

4 spaces 
echo "    " | ./entab 5 9 13 | od -An -t x1
Expected output:  09 0a

7 spaces
echo "        " | ./entab 5 9 13 | od -An -t x1
Exptected output: 09 20 20 20 0a 

12 spaces
echo "            " | ./entab 5 9 13 | od -An -t x1
Exptected output: 09 09 09 0a 
tab 5, tab 9, tab 13

12 spaces
echo "            " | ./entab | od -An -t x1
Exptected output: 09 20 20 20 20 0a 
tab 8, space, space, space, space

*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define DEFAULT_TAB 8
#define MAXSTOPS 100

int mygetline(char s[], int lim) {
    int c = ' ';
    int i = 0;

    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = (char)c;
    if (c == '\n')
        s[i++] = '\n';
    s[i] = '\0';
    return i;
}

/* If currently in column col (0-based), what column is the next tab stop? */
static int nextstop(int col, const int *stops, int nstops) {
    if (nstops > 0) {
        for (int i = 0; i < nstops; i++)
            if (stops[i] > col) return stops[i];
        /* beyond last explicit stop: revert to default repeating tabs */
    }
    return col + (DEFAULT_TAB - (col % DEFAULT_TAB));
}

/* entab: replace strings of blanks with tabs + blanks */
static void entab(const char s[], int len, const int *stops, int nstops) {
    int col = 0;      /* current output column (0-based) */
    int blanks = 0;   /* pending blanks not yet emitted */

    for (int i = 0; i < len; i++) {
        char c = s[i];

        if (c == ' ') {
            blanks++;
            /* If emitting these blanks would land exactly on a tab stop, use a tab */
            if (col + blanks == nextstop(col, stops, nstops)) {
                putchar('\t');
                col += blanks;   /* we advanced by blanks columns */
                blanks = 0;
            }
            continue;
        }

        /* flush pending blanks before non-blank */
        while (blanks > 0) {
            putchar(' ');
            blanks--;
            col++;
        }

        putchar(c);

        if (c == '\n') {
            col = 0;
        } else if (c == '\t') {
            col = nextstop(col, stops, nstops);
        } else {
            col++;
        }
    }

    /* flush any trailing blanks */
    while (blanks > 0) {
        putchar(' ');
        blanks--;
        col++;
    }
}

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    int stops[MAXSTOPS];
    int nstops = 0;

    /* Parse tab stops as increasing column numbers (0-based or 1-based?) */
    /* Here: treat argv values as 1-based columns (more natural), convert to 0-based. */
    for (int i = 1; i < argc && nstops < MAXSTOPS; i++) {
        
        int v = atoi(argv[i]);  // Read argument

        if (v > 0) {    // Only valid characters 

            int col = v - 1; /* convert to 0-based */

             // The first position is always accepted. 
             // Next arg must be bigger than the last stored
            if (nstops == 0 || col > stops[nstops - 1]) {  
                stops[nstops++] = col;  
            }
        }
    }

    int len;

    while ((len = mygetline(line, MAXLINE)) > 0)
        entab(line, len, stops, nstops);

    return 0;
}
