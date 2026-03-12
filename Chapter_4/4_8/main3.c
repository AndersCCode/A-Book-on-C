/* Suppose that there will never be more than one character of pushback. 
Modify getch and an ungetch accordingly. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define MAXVAL 100  /* maximum depth of val stack */
#define BUFSIZE 100 /* getch and ungetch */
#define MAXVAR 26

/* external variables */
int sp = 0;             /* stack pointer */
double val[MAXVAL];     /* stack of values */

static int bufchar = 0;     /* The pushed-back character */
static int bufempty = 1;    /* 1 = buffer empty, 0 = one character is waiting */

double variables[MAXVAR] = {0.0}; /* Array for variables initialized to 0 */
double last_printed = 0.0;
 
/* push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else 
        printf("error: stack full, can't push %g\n", f);
}

/* pop and return top value from value stack */
double pop(void) {
    if (sp > 0)
        return val[--sp]; // decrement first (sp-1), then read the new sp
    else {
        printf("pop error: value stack empty \n");
        return 0.0;
    }
}

void duplicate_top(void) {
    if (sp > 0) {
        push(val[sp-1]);          
    } else {
        printf("duplicate error: value stack empty\n");
    }
}

void print_top_of_stack(void) {
    if (sp > 0)
        printf("Top stack element is: %.8g\n", val[sp-1]);
    else {
        printf("print top of stack error: value stack empty \n");
    }
}

void print_value_stack(void) {
    if (sp == 0) {
        printf("print stack error: value stack empty \n");
        return;
    }
    
    printf("Value stack (%d elements):\n", sp);
    for (int i = sp - 1; i >= 0; i--) 
        printf("  %s[%d] = %.8g\n", (i == sp-1) ? "top→ " : "     ", i, val[i]);
}

void print_variables(void) {
    for (int i = 0; i < MAXVAR; i++)
        printf("%c = %g%c", 'A' + i, variables[i], (i%10==9 || i == MAXVAR-1) ? '\n' : ' ');  
}

/* get a (possibly pushed back) character */
int getch(void) {
    if (bufempty == 0) { // if bufempty is false (a character is waiting)
        bufempty = 1;
        return bufchar;
    } else {
        return getchar(); // Get new character
    }
}

/* push character back on input */
void ungetch(int c) {
    if (bufempty == 0) { // Buffer is full
        printf("Ungetch: Too many characters\n");
    } else {
        bufchar = c;
        bufempty = 0;
    }

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

    if (c == '-') {
        s[i++] = c;
        c = getch();
        if (!isdigit(c) && c != '.') {
            ungetch(c);
            return '-';
        }
    }
    s[i++] = c;   // store first digit (or the char after sign)

    while (isdigit(s[i++] = c = getch()))
        ;

    if (c == '.')
        while (isdigit(s[i++] = c = getch()))
            ;
    s[--i] = '\0';

    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

int main(void) {
    int type;
    double op2;
    char s[MAXOP];

    printf("Reverse Polish calculator\n");
    printf("Commands (lowercase):\n");
    printf("c=clear, s=swap, d=duplicate, t=top, a=all, v=variables, r=result+print, l=show last\n\n");
    printf("Variables: uppercase A-Z\n");
    printf("42 A r --> A = 42, A= (A is assigned top value of stack)\n\n");
    printf("Enter expressions in RPN, press r to show result\n");   
    printf("Ctrl+C to quit\n\n");

    //ungets("hello");
    //printf("Testing ungets: should now read 'h','e','l','l','o'\n");

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
                break;
            case 't':
                print_top_of_stack();
                break;
            case 'a':
                print_value_stack();
                break;
            case 'v':
                print_variables();
                break;
            case 'r':
                if (sp > 0) {
                    last_printed = pop();
                    printf("Result:\t%.8g\n", last_printed); 
                } else {
                    printf("Nothing to calculate yet\n");
                }
                break;   
            case 'l':
                printf("Last printed:\t%.8g\n", last_printed); 
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

            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I':
            case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
            case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':

                int var = s[0] - 'A';

                int x = getch();
            
                if (x == '=') { 
                    if (sp > 0) {
                        variables[var] = pop();
                        printf("assigned %.8g to %c\n", variables[var], s[0]);
                    } else {
                        printf("Stack is empty. No assignment made.\n");
                    }                         
                } else {
                    ungetch(x);
                    push(variables[var]);
                }
            break; 

            default:
                printf("error: unknown command %c\n", type);
                break;            
        }
    }
return 0;
}



