/* Our version of getword doesn not properly handle underscores, string constants, comments, 
or preprocessor control lines. Write a better version

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
    {"/* ... */", 0},
    {"__FILE__", 0},
    {"__abc__", 0},
    {"_temp", 0},
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"my_var", 0},
    {"unsigned", 0},
    {"var_123_test", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

char buf[BUFSIZE];      // Buffer for ungetch
int bufp = 0;           // Next free position in buf

// Find word in tab[0]...tab[n-1]
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

// Get a (possibly pushed back) character
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

// Push character back on input
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many charachters\n");
    else 
        buf[bufp++] = c;
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;

    // skip whitespaces
    while (isspace(c = getch()))
        ;
    
    // Read first charachter
    if (c != EOF)
        *w++ = c;
    
    // If it's not the start of an identifier, return it as is.
    if (!isalpha(c) && (c != '_')) {    // c is not a letter and not and underscore
        *w = '\0';
        return c;
    }

    // Now read the rest of the identifier (letters, digits or underscore)
    for ( ; --lim > 0; w++) {
        // *w = getch();
        c = getch();        // read first

        if (!isalnum(c) && c != '_') { // check before storing to w
            ungetch(c);
            break;
        }

        *w = c;
    }
    *w = '\0';
    
    return word[0];
}

// Count C keywords
int main(void) 
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) || (word[0] == '_'))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    
    for (n = 0; n < (int)NKEYS; n++) 
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);

    return 0;
}