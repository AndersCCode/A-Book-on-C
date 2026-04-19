/* Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing.
Good possibilities include getline (Chapter 1 and 4), atoi, itoa, and their variants (Chapter 2, 3 and 4), 
reverse (Chapter 3), and strindex and getop (Chapter 4). */

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
double val[MAXVAL];     /* stack of values */
double *sp = val;             /* stack pointer */

double variables[MAXVAR] = {0.0}; /* Array for variables initialized to 0 */
double *vp = variables;
double last_printed = 0.0;
 
/* push f onto value stack */
void push(double f) {
    if (sp < val + MAXVAL) {
        *sp++ = f;
    }
    else 
        printf("error: stack full, can't push %g\n", f);
}

/* pop and return top value from value stack */
double pop(void) {
    if (sp > val)
        return *--sp; // decrement first, then read the new sp
    else {
        printf("pop error: value stack empty \n");
        return 0.0;
    }
}

void duplicate_top(void) {
    if (sp > val) {
        push(*(sp - 1));          
    } else {
        printf("duplicate error: value stack empty\n");
    }
}

void print_top_of_stack(void) {
    if (sp > val)
        printf("Top stack element is: %.8g\n", *(sp - 1));
    else {
        printf("print top of stack error: value stack empty \n");
    }
}

void print_value_stack(void) {
    
    if (sp == val) {
        printf("print stack error: value stack empty \n");
        return;
    }
    
    printf("Value stack bottom --> top (%ld elements):\n", sp - val);
    
    for (double *p = val; p < sp; p++) {    // use a temporary pointer p
        printf("  %s%.8g\n", (p == sp - 1) ? "top→ " : "     ", *p);
    }
}

void print_variables(void) {

    int i = 0;

    for (double *p = variables; p < variables + MAXVAR; p++, i++) {
        printf("%c = %g%c", 'A' + i, *p, (i%10==9 || i == MAXVAR-1) ? '\n' : ' ');  
    }
}

/* get next operator, numeric operand or variable letter 
    Returns:
    NUMBER          if a number was found
    the character   if it's an operator (+ - * / % etc.) 
    a letter        if it's a variable name (A-Z)
    */
int getop(char *s) {
    int c;
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
        *s = '\0';
        return EOF;
    }

    *s++ = c;
    *s = '\0';
    
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
        int next = getchar();
        
        if (!isdigit(next) && next != '.') {
            if (next != EOF) lastc = next;
            return '-';
        } 
        *s++ = next;        // write the first digit after the minus
        c = next;
    }
    else if (!isdigit(c) && c != '.') {
        return c;       // operator
    }

    /* Collect integer part */
    while (isdigit(*s++ = c = getchar()))
        ;

    /* Collect fractional part if present */
    if (c == '.') {
        while (isdigit(*s++ = c = getchar()))
            ;
    }

    *s-- = '\0';

    if (c != EOF)
        lastc = c;

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

    while ((type = getop(s)) != EOF) {
        switch (type) {
            
            case NUMBER:
                push(atof(s));
                break;

            case VAR_ASSIGN: {
                // We just read A= , the variable letter is still in s[0]
                int var = *s - 'A';
                if (sp > val) {
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
                if (sp == val + 1) {
                    push(sin(pop()));
                }
                else {
                    printf("Sin calculation error: need at least one element\n");
                }
                break;

            case 'w':
                if (sp >= val + 2) {
                    double op2 = pop(); // Exponent comes first. Was pushed last
                    double op1 = pop(); // Base

                    push(pow(op1, op2));
                }
                else {
                    printf("Pow calculation error: need two elements\n");
                }
                break;
            case 'e':
                if (sp == val + 1) {
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
                if (sp > val) {
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
                printf("Stackpointer (next position to push) = %p (index %d)\n", (void*)sp, (int)(sp - val)); 
                break;   
            case 'd':
                duplicate_top();
                break;  
            case 's':
                if (sp >= val + 2) {
                    double temp = *(sp-1);
                    *(sp-1) = *(sp-2);
                    *(sp-2) = temp;
                } else {
                    printf("swap error: need at least two elements\n");
                }
                break;
            case 'c':
                sp = 0;  //val
                printf("Stack cleared\n");
                break;

            default:
                printf("error: unknown command %c\n", type);
                break;            
        }
    }
return 0;
}



