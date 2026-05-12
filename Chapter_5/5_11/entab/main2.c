/* Modify the programs entab and detab (written as exercises in Chapter 1) 
to accept a list of tab stops as arguments. Use the default tab settings 
if there are no arguments. 

entab - replace strings of blanks by the minimum number of tabs and blanks
to achieve the same spacing. 

i.e. 9 spaces should be translated to 1 tab and 1 space */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define DEFAULT_TAB 8

int mygetline(char s[], int lim) {
    int c, i = 0;
    while (i < lim-1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = '\n';
    s[i] = '\0';
    return i;
}

/* entab: replace strings of blanks with tabs + blanks */
void entab(char s[], int len, int tabstop) {
    int i, pos = 0;           // current column position

    for (i = 0; i < len; ++i) {
        if (s[i] == ' ') {
            ++pos;
            // Check if we hit a tab stop
            if (pos % tabstop == 0) {
                putchar('\t');
                pos = 0;        // reset after tab
            }
        } 
        else {
            // Output any pending spaces that didn't reach tab stop
            while (pos > 0) {
                putchar(' ');
                --pos;
            }
            putchar(s[i]);
            if (s[i] == '\t')
                pos = 0;                    // tab resets position
            else if (s[i] == '\n')
                pos = 0;
            else
                pos++;
        }
    }

    // trailing spaces at end of line
    while (pos > 0) {
        putchar(' ');
        --pos;
    }
}

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    int len;
    int tabstop = DEFAULT_TAB;

    // TODO: parse command line arguments for tab stops
    if (argc > 1) {
        tabstop = atoi(argv[1]);   // simple case: first arg = tabstop
        if (tabstop <= 0) tabstop = DEFAULT_TAB;
    }

    while ((len = mygetline(line, MAXLINE)) > 0)
        entab(line, len, tabstop);

    return 0;
}


for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
        // handle -m  (starting position)
    }
    else if (argv[i][0] == '+') {
        // handle +n  (increment)
    }
    else {
        // plain number → explicit tab stop position
    }
}