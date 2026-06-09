/* Our version of getword does not properly handle underscores, string constants,
comments, or preprocessor control lines. Write a better version.

gcc -Wall -Wextra -O2 -o keyword_count main.c

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
#define NKEYS (sizeof keytab / sizeof(keytab[0]))

struct key {
    char *word;
    int count;
};

struct key keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"do", 0},
    {"double", 0},
    {"else", 0},
    {"enum", 0},
    {"extern", 0},
    {"float", 0},
    {"for", 0},
    {"goto", 0},
    {"if", 0},
    {"int", 0},
    {"long", 0},
    {"register", 0},
    {"return", 0},
    {"short", 0},
    {"signed", 0},
    {"sizeof", 0},
    {"static", 0},
    {"struct", 0},
    {"switch", 0},
    {"typedef", 0},
    {"union", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

int buf[BUFSIZE];      /* Buffer for ungetch */
int bufp = 0;          /* Next free position in buf */

/* Find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high ) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else 
            return mid;
    }
    return -1;
}

/* Get a (possibly pushed back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* Push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else if (c != EOF)
        buf[bufp++] = c;
}

int isident(int c)
{
    return isalnum((unsigned char)c) || c == '_';
}

void skip_comment(int *at_line_start)
{
    int c, prev;

    prev = 0;
    while ((c = getch()) != EOF) {
        if (c == '\n')
            *at_line_start = 1;
        if (prev == '*' && c == '/')
            break;
        prev = c;
    }
}

void skip_line_comment(int *at_line_start)
{
    int c;

    while ((c = getch()) != EOF && c != '\n')
        ;
    if (c == '\n')
        *at_line_start = 1;
}

void skip_quoted(int quote, int *at_line_start)
{
    int c;

    while ((c = getch()) != EOF) {
        if (c == '\\') {
            if (getch() == EOF)
                break;
        } else if (c == quote) {
            break;
        } else if (c == '\n') {
            *at_line_start = 1;
            break;
        }
    }
}

void skip_preprocessor(int *at_line_start)
{
    int c, escaped;

    escaped = 0;
    while ((c = getch()) != EOF) {
        if (c == '\n') {
            if (escaped) {
                escaped = 0;
                continue;
            }
            *at_line_start = 1;
            break;
        }
        escaped = (c == '\\');
    }
}

int getword(char *word, int lim)
{
    int c, next;
    int started_at_line_start;
    char *w;
    static int at_line_start = 1;

    w = word;

    for (;;) {
        c = getch();
        if (c == EOF) {
            *w = '\0';
            return EOF;
        }

        if (c == '\n') {
            at_line_start = 1;
            continue;
        }
        if (isspace((unsigned char)c))
            continue;

        if (c == '#' && at_line_start) {
            skip_preprocessor(&at_line_start);
            continue;
        }

        started_at_line_start = at_line_start;
        at_line_start = 0;

        if (c == '/') {
            next = getch();
            if (next == '*') {
                at_line_start = started_at_line_start;
                skip_comment(&at_line_start);
                continue;
            }
            if (next == '/') {
                skip_line_comment(&at_line_start);
                continue;
            }
            ungetch(next);
        } else if (c == '"' || c == '\'') {
            skip_quoted(c, &at_line_start);
            continue;
        }

        break;
    }

    *w++ = c;
    --lim;
    if (!isalpha((unsigned char)c) && c != '_') {
        *w = '\0';
        return c;
    }

    while ((c = getch()) != EOF && isident(c)) {
        if (lim > 1) {
            *w++ = c;
            --lim;
        }
    }

    if (c != EOF)
        ungetch(c);
    *w = '\0';
    
    return word[0];
}

/* Count C keywords */
int main(void) 
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha((unsigned char)word[0]) || word[0] == '_')
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    
    for (n = 0; n < (int)NKEYS; n++) 
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);

    return 0;
}