/* As written, getint treats a + or - not followed by a digit as a valid representation of zero. 
Fix it to push such a character back on the input */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFSIZE 100

char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in the buf */

 int getch(void) 
 {
    return (bufp > 0) ? buf[--bufp] : getchar();
 }

 void ungetch(int c)
 {
    if (bufp > BUFSIZE)
        printf("ungetch: too many characters\n");
    else 
        buf[bufp++] = c;
 }

 /* getint: get next integer from input into *pn */
 int getint(int *pn)
 {
    int c, sign;

    while (isspace(c = getch()))    /* skip white space */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-'){
        ungetch(c);      /* it's not a number, put back the character */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;     /* decide sign */
    
    if (c == '+' || c == '-')
        c = getch();    /* read next character */

        if (!isdigit(c)) {                      /* + or - followed by a digit */
            ungetch(c);                         /* push back the non-digit */
            ungetch(sign == 1 ? '+' : '-');     /* push back the sign */
            return 0;
        }
    /* now we know we have at least one digit */
    for (*pn = 0; isdigit(c); c = getch())  /* read the number*/
        *pn = 10 * *pn + (c - '0');
        
    *pn *= sign;    /* Assign the sign */
        
    if (c != EOF)   /* The first character (after the number) that is not a digit */
        ungetch(c);
    
    return c;
 }

 int main(void) 
 {
    int n, ret;

    printf("Type numbers. CTRL-C to quit.\n\n");

    while ((ret = getint(&n)) != EOF) {
        
        if (ret == 0) {
            printf("No number (character skipped))\n");
            getch();
            continue;
        } 
            

        /* We got a real number */
        printf("Number: %d", n);

        if (ret == '\n')
            printf("    (followed by newline)\n");
        else if (isspace(ret))
            printf("    (followed by whitespace)\n");
        else 
            printf("    (followed by '%c')\n", ret);
    }

    printf("Reached end of input.\n");
    return 0;
 }