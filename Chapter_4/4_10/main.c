/* An alternate organization uses getline to read an entire input line; 
this makes getch and ungetch. Revise the calculator to use this approach. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100       /* max size of operand or operator */
#define NUMBER '0'      /* signal that a number was found */
#define MAXVAL 100      /* maximum depth of val stack */
#define BUFSIZE 100     /* getch and ungetch */
#define MAXVAR 26       /* maximum number of variables */
#define MAXLINE 1000    /* maximum length of input line */

/* external variables */
int sp = 0;             /* stack pointer */
double val[MAXVAL];     /* stack of values */

double variables[MAXVAR] = {0.0}; /* Array for variables initialized to 0 */
double last_printed = 0.0;

char line[MAXLINE];     /* Array to contain input line */
 
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

int get_line(char s[], int lim) {
    int c, i = 0;

    for (i = 0; i <lim-1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n')
        s[i] = c;
        ++i;

    s[i] = '\0';
    return i;
}

/* get next operator, numeric operand or variable letter 
    Returns:
    NUMBER          if a number was found
    the character   if it's an operator (+ - * / % etc.) 
    a letter        if it's a variable name (A-Z)
    */
int getop(char s[], char line[], int *pos) {
    int i, c;

    // skip trailing spaces
    while ((c = line[*pos]) == ' ' || c == '\t')
        (*pos)++;
    
    if (c == '\0' || c == '\n') {
        return EOF;
    }

    i = 0;
    s[i++] = c;     // store a "real character"
    (*pos)++;

    if (!isdigit(c) && c != '.' && c != '-')        // variable ?
        return c;

    /* Handle possible negative number or just a starting digit/dot */
    if (c == '-') {
        c = line[*pos];
        if (!isdigit(c) && c != '.') {  // binary operator ?
            (*pos)--;                   // back up one position
            return '-';
        }
        s[i++] = c;     // store '-'
        (*pos)++;
    }

    // Read the rest of the number
    while (isdigit(s[i++] = c = line[(*pos)++]))        // read part before .
        ;


    if (c == '.') {
        while (isdigit(s[i++] = c = line[(*pos)++]))    // read part after .
            ;
    }

    s[--i] = '\0';

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


    while (get_line(line, MAXLINE) > 0) {
        int pos = 0;

        while (1) {
            int type = getop(s, line, &pos);

            if (type == EOF || line[pos] == '\0')
                break;
        
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
                case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z': {

                    int var = type - 'A';       // type is already the letter we read

                    // Look at the **next character** without comsuming it yet
                    if (pos < MAXLINE && line[pos] == '=') {
                        pos++;  // consume the '='

                        if (sp > 0) {
                            variables[var] = pop();
                            printf("Assigned %.8g to %c\n", variables[var], type);
                        } else {
                            printf("Stack is empty. No assignment made.\n");
                        }    
                    }
                    else {
                        // not assignment → push variable value
                        push(variables[var]);
                    }
                }
                break; 

                default:
                    printf("error: unknown command %c\n", type);
                    break;            
            }
        }
    }
return 0;
}



