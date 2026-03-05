/* Given the basic framework, it's straightforward to extend the calculator. Add the modulus (%) operator 
and provisions for negative numbers */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define MAXVAL 100  /* maximum depth of val stack */
#define BUFSIZE 100 /* getch and ungetch */

/* external variables */
int sp = 0;             /* stack pointer */
double val[MAXVAL];     /* stack of values */

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;   /* next free position in buf */

/* push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else 
        printf("error: stack full, can't push %g\n", f);
}

/* pop and return top value from stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty \n");
        return 0.0;
    }
}

/* get a (possibly pushed back) character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else    
        buf[bufp++] = c;
}

/* get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c;               /* not a number */

    i = 0;
    if (c == '-') {                     /* possible negative number */
        int next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);              /* it was the binary minus operator */
            return '-';
        }
        s[i++] = '-';                   /* start of negative number */
        c = next;                       /* continue with the digit or '.' */
    }

    if (isdigit(c))                     /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')                       /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';

    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

int main(void) {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-': // order of operands is important
                op2 = pop();
                push(pop() - op2);
                break;
            case '/': // order of operands is important
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else 
                    printf("error: zero divisor\n");
                break;
            case '%': // order of operands is important
                op2 = pop();
                if (op2 != 0.0)
                    push((int)pop() % (int)op2);  // % only support int
                    //push(fmod(pop(), op2)); // fmod has however support for float. Kräver -lm vid kompilering
                else 
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop()); // Enter is pressed, print result
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}