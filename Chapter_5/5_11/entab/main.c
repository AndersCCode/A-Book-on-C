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

#define MAXLINE     1000
#define DEFAULT_TAB 8
#define MAXTABS     100   /* max number of tab stops we accept */

int mygetline(char s[], int lim) {
    int c, i = 0;
    while (i < lim-1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = '\n';
    s[i] = '\0';
    return i;
}

/* Return the next tab stop position after or at `col` */
int nexttabstop(int col, int tabs[], int ntabs) {
    if (ntabs == 0) {                     /* default every DEFAULT_TAB */
        return ((col / DEFAULT_TAB) + 1) * DEFAULT_TAB;
    }

    for (int i = 0; i < ntabs; ++i) {
        if (tabs[i] > col)
            return tabs[i];
    }
    /* beyond last tab stop → continue with last interval */
    if (ntabs >= 2)
        return tabs[ntabs-1] + (tabs[ntabs-1] - tabs[ntabs-2]);
    return tabs[0] + DEFAULT_TAB;   /* fallback */
}

/* entab: replace strings of blanks with tabs + blanks */
void entab(char s[], int len, int tabs[], int ntabs) {
    int i, col = 0;          /* current column */
    int blanks = 0;          /* pending spaces */

    for (i = 0; i < len; ++i) {
        if (s[i] == ' ') {
            ++blanks;
            ++col;
        } else {
            /* output pending blanks using tabs where possible */
            while (blanks > 0) {
                int nextstop = nexttabstop(col - blanks, tabs, ntabs);
                int dist = nextstop - (col - blanks);

                if (dist <= blanks && dist > 0) {
                    putchar('\t');
                    blanks -= dist;
                    col = nextstop;          /* tab lands exactly on stop */
                } else {
                    /* can't reach next stop with remaining blanks */
                    while (blanks > 0) {
                        putchar(' ');
                        --blanks;
                        ++col;
                    }
                }
            }

            putchar(s[i]);

            if (s[i] == '\t') {
                /* real tab in input resets to next stop */
                col = nexttabstop(col, tabs, ntabs);
            } else if (s[i] == '\n') {
                col = 0;
            } else {
                ++col;
            }
        }
    }

    /* trailing blanks at end of input/line */
    while (blanks > 0) {
        int nextstop = nexttabstop(col - blanks, tabs, ntabs);
        int dist = nextstop - (col - blanks);
        if (dist <= blanks && dist > 0) {
            putchar('\t');
            blanks -= dist;
            col = nextstop;
        } else {
            while (blanks > 0) {
                putchar(' ');
                --blanks;
                ++col;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    int len;
    int tabs[MAXTABS];
    int ntabs = 0;

    /* Parse tab stops from command line */
    for (int i = 1; i < argc && ntabs < MAXTABS; ++i) {
        int stop = atoi(argv[i]);
        if (stop > 0)
            tabs[ntabs++] = stop;
    }

    /* Optional: sort the tab stops (good practice) */
    for (int i = 0; i < ntabs; ++i) {
        for (int j = i+1; j < ntabs; ++j) {
            if (tabs[j] < tabs[i]) {
                int tmp = tabs[i];
                tabs[i] = tabs[j];
                tabs[j] = tmp;
            }
        }
    }

    while ((len = mygetline(line, MAXLINE)) > 0)
        entab(line, len, tabs, ntabs);

    return 0;
}