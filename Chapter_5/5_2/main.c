/* Write getfloat, the floating point analog of getint. What type does getfloat return as its function value? */

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
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else 
        buf[bufp++] = c;
 }

 /* getfloat: get next float from input into *pn */
int getfloat(float *pn)
 {
    int c, sign;
    float power = 1.0;              /* for the fractional part: 0.1, 0.01, etc. */

    while (isspace(c = getch()))    /* skip white space */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);      /* it's not a number, put back the character */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;     /* decide sign */
    
    if (c == '+' || c == '-')
        c = getch();    /* read next character */

        if (!isdigit(c) && c != '.') {          /* + or - or . followed by a digit */
            ungetch(c);                         /* push back the non-digit */
            ungetch(sign == 1 ? '+' : '-');     /* push back the sign */
            return 0;
        }
    /* Read the integer part */
    for (*pn = 0.0; isdigit(c); c = getch())  /* read the number*/
        *pn = 10.0 * *pn + (c - '0');
    
    /* Read the fractional part if present */
    if (c == '.') {
        c = getch();

        for (power = 1.0; isdigit(c); c = getch()) {
            *pn = 10.0 * *pn + (c - '0');
            power *= 10.0;
        }
            
    }
        
    *pn = sign * (*pn / power);    /* Apply the sign and divide by power for fraction */
        
    if (c != EOF)   /* The first character (after the number) that is not a digit */
        ungetch(c);
    
    return c;
 }

 int main(void) 
 {
    float val;
    int ret;

    printf("Type floating-point numbers. CTRL-C to quit.\n\n");

    while ((ret = getfloat(&val)) != EOF) {
        
        if (ret == 0) {
            printf("No float number (character skipped)\n");
            getch();
            continue;
        } 
            
        printf("Float: %g", val);

        if (ret == '\n')
            printf("    [followed by newline]\n");
        else if (isspace(ret))
            printf("    [followed by whitespace]\n");
        else 
            printf("    [followed by '%c']\n", ret);
    }

    printf("Reached end of input.\n");
    return 0;
 }