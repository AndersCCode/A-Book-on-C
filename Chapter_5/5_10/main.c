/* Modify getop so that it doesn't need to use ungetch.
Hint: use an internal static variable. */

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

/* get next operator, numeric operand or variable letter 
    Returns:
    NUMBER          if a number was found
    the character   if it's an operator (+ - * / % etc.) 
    a letter        if it's a variable name (A-Z)
    */
int getop(char s[]) {
    int i, c;
    static int lastc = EOF;

    /* Get first non-whitespace character, using static pushback if present */
    if (lastc != EOF) {
        c = lastc;
        lastc = EOF;
    } else {
        c = getchar();
    }

    /* Skip all whitespaces (spaces, tabs, newlines) */
    while (c == ' ' || c == '\t' || c == '\n') {
        c = getchar();
    }

    if (c == EOF) {
        s[0] = '\0';
        return EOF;
    }

    s[0] = c;
    s[1] = '\0';
    
    i = 0;

    /* Variable handling: A or A= */
    if (isupper(c)) {
        int next = getchar();
        if (next == '=') {
            return VAR_ASSIGN;
        } else {
            if (next != EOF)
                lastc = next;
            return c;               // just the variable letter
        }
    }

    /* Number or operator handling */
    if (c == '-') {
        s[i++] = '-';
        c = getchar();
        if (!isdigit(c) && c != '.') {
            if (c != EOF)
                lastc = c;
            return '-';
        }
        s[i++] = c;
    } else if (isdigit(c) || c == '.') {
        s[i++] = c;
    } else {
        return c;                   // operator or other single char
    }

    /* Collect integer part */
    while (isdigit(s[i++] = c = getchar()))
        ;

    /* Collect fractional part if present */
    if (c == '.') {
        while (isdigit(s[i++] = c = getchar()))
            ;
    }

    s[--i] = '\0';

    if (c != EOF)
        lastc = c;

    return NUMBER;
}

int main(int argc, char *argv[]) {
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

    while (--argc > 0)
    while ((type = getop(s)) != EOF) {
        switch (type) {
            
            case NUMBER:
                push(atof(s));
                break;

            case VAR_ASSIGN: {
                // We just read A= , the variable letter is still in s[0]
                int var = s[0] - 'A';
                if (sp > 0) {
                    variables[var] = pop();
                    printf("assigned %.8g to %c\n", variables[var], s[0]);
                } else {
                    printf("Stack is empty. No assignment made.\n");
                }
                break;
            }

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

            default:
                printf("error: unknown command %c\n", type);
                break;            
        }
    }
return 0;
}



