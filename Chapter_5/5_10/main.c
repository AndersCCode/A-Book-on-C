/* Write a program expr, which evaluates a reverse Polish expression 
from the command line, where each operator or operand is a separate 
argument */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define MAXVAL 100  /* maximum depth of val stack */
#define MAXVAR 26
#define VAR_ASSIGN '='

/* external variables */
int sp = 0;             /* stack pointer */
double val[MAXVAL];     /* stack of values */
 
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

int main(int argc, char *argv[]) {
   
    double op2;

    if (argc < 2) {
        printf("Usage: expression \n");
        
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        
        char *arg = argv[i];
 
        if (isalnum(*arg)) {
            push(atof(arg));
        } else if (strlen(arg) == 1) {
            char op = arg[0];

            switch (op) {
                case '+':
                    printf("%g\n", pop() + pop());
                    break;
                case '*':
                    printf("%g\n", (pop() * pop()));
                    break;
                case '-': // order of operands is important
                    op2 = pop();
                    printf("%g\n", pop() - op2);
                    break;
                case '/': // order of operands is important
                    op2 = pop();
                    if (op2 != 0.0) {
                        printf("%g\n", pop() / op2);
                    }
                    else 
                        printf("error: zero divisor\n");
                    break;
                default:
                    printf("error: unknown command %s\n", *argv);
                    break;            
            }
        }
    }
return 0;
}



