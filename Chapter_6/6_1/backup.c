/* Our version of get_word doesn not properly handle underscores, string constants, comments, 
or preprocessor control lines. Write a better version

gcc -Wall -Wextra -O2 -o keyword_count main.c

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
#define NKEYS (sizeof key_table / sizeof(key_table[0]))

struct key {
    char *word;
    int count;
};

struct key key_table[] = {
    {"auto", 0}, {"break", 0}, {"case", 0}, {"char", 0},
    {"const", 0}, {"continue", 0}, {"default", 0}, {"do", 0},
    {"double", 0}, {"else", 0}, {"enum", 0}, {"extern", 0},
    {"float", 0}, {"for", 0}, {"goto", 0}, {"if", 0},
    {"int", 0}, {"long", 0}, {"register", 0}, {"return", 0},
    {"short", 0}, {"signed", 0}, {"sizeof", 0}, {"static", 0},
    {"struct", 0}, {"switch", 0}, {"typedef", 0}, {"union", 0},
    {"unsigned", 0}, {"void", 0}, {"volatile", 0}, {"while", 0}
};

char buf[BUFSIZE];      /* Buffer for ungetch */
int bufp = 0;           /* Next free position in buf */

int binary_search(char *word, struct key tab[], int n);
int getch(void);
void ungetch(int c);
int get_word(char *word, int lim);
void skip_string(int quote);                                                                                                                                                                         

int main(void) 
{
    int n;
    char word[MAXWORD];

    while (get_word(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) || (word[0] == '_'))
            if ((n = binary_search(word, key_table, NKEYS)) >= 0)
                key_table[n].count++;
    }

    for (n = 0; n < (int)NKEYS; n++) 
        if (key_table[n].count > 0)
            printf("%4d %s\n", key_table[n].count, key_table[n].word);

    return 0;
}

int binary_search(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high ) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1; // word on the left side of mid
        else if (cond > 0)
            low = mid + 1;  // word is on the right side of mid
        else 
            return mid; // word is found
    }
    return -1;
}

int get_word(char *word, int lim)
{
    int c;
    char *w = word;

    /* Skip whitespace. Any newline we pass means the next non-white space
    token will be at the beginning of a line */
    while (isspace(c = getch())) {
        ;
    }

    if (c == EOF)   // Ctrl + D
        return EOF;
    
    // If it's not the start of an identifier, return it as is.
    if (!isalpha(c) && (c != '_')) {    // c is not a letter and not and underscore
        *w = '\0';
        return c;
    }
   
    /* string literal */
    /*if (c == '"') {
        printf("[Debug] String literal - Never reached ?");
        skip_string('"');
        return get_word(word, lim);     // get next token
    }

     /* character constant */
    /*if (c == '\'') {
        printf("[Debug] String literal - Never reached ?");
        skip_string('\'');
        return get_word(word, lim);     // get next token
    }*/

    // Save character before proceeding to the next
    *w = c;
    w++;

    // Now read the rest of the identifier (letters, digits or underscore)
    for ( ; --lim > 0; w++) {
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

/* Consume every character up to and including the matching closing quote. 
get_word has already read the opening quote. */
void skip_string(int quote)
{
    int c;

    while ((c = getch()) != EOF) {
        if (c == quote)     // Found the closing quote, which was the goal.
            return;
        }
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
        printf("ungetch: too many charachters\n");
    else 
        buf[bufp++] = c;
}


