/* Add access to library functions like sin, exp and pow. 

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
        return val[--sp]; // decrement first (sp-1), then read the new sp
    else {
        printf("pop error: stack empty \n");
        return 0.0;
    }
}

void duplicate_top(void) {
    if (sp > 0) {
        push(val[sp-1]);          
    } else {
        printf("duplicate error: stack empty\n");
    }
}

void print_top_of_stack() {
    if (sp > 0)
        printf("Top stack element is: %.8g\n", val[sp-1]);
    else {
        printf("print top of stack error: stack empty \n");
    }
}

void print_stack() {
    if (sp == 0) {
        printf("print stack error: stack empty \n");
        return;
    }
    
    printf("stack (%d elements):\n", sp);
    for (int i = sp - 1; i >= 0; i--) {
        printf("  %s[%d] = %.8g\n", (i == sp-1) ? "top→ " : "     ", i, val[i]);
            //printf("Element s[%d] = %g\n", i, val[i]);
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
            case 'n':
                if (sp == 1) {
                    push(sin(pop()));
                }
                else {
                    printf("Sin calculation error: need at least one element\n");
                }
                break;
            case 'w':
                if (sp >= 2) {
                    double op2 = pop(); // Exponent comes first. Was pushed last
                    double op1 = pop(); // Base

                    push(pow(op1, op2));
                }
                else {
                    printf("Pow calculation error: need two elements\n");
                }
                break;
            case 'e':
                if (sp == 1) {
                    push(exp(pop()));
                }
                else {
                    printf("Exp calculation error: need one element\n");
                }
                break;
                
            case '\n':
                //printf("Result:\t%.8g\n", pop());
                break;
            case 't':
                print_top_of_stack();
                break;
            case 'a':
                print_stack();
                break;
            case '=':
                printf("Result:\t%.8g\n", pop()); 
                break;    
            case 'i':
                printf("Stackpointer (next position to push) = %d\n", sp); 
                break;   
            case 'd':
                duplicate_top();
                break;  
            case 's':
                if (sp >= 2) {
                    double temp = val[sp-1];
                    val[sp-1] = val[sp-2];
                    val[sp-2] = temp;
                } else {
                    printf("swap error: need at least two elements\n");
                }
                break;
            case 'c':
                sp = 0;
                printf("Stack cleared\n");
                break;
            default:
                printf("error: unknown command %c\n", type);
                break;
            
        }
    }
    return 0;
}