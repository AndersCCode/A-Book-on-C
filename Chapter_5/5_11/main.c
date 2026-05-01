/* /* Modify the programs entab and detab (written as exercises in Chapter 1) to accept 
a list of tab stops as arguments. Use the default tab settings if there are no arguments. */ */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define TABSTOP 4   // Tab stops every TABSTOP columnns

int main(int argc, char *argv[])
{
    int c;
    int column = 0;   /* current position on the line */

    if (argc < 2) {
        printf("Usage: ./expr expression...\n");
        
        return 1;
    }

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            do {
                putchar(' ');
                ++column;
            } while (column % TABSTOP != 0);
        } else if (c == '\n') {
            putchar('\n');
            column = 0;
        } else {
            putchar(c);
            ++column;
        }
    }
    return 0;
}
    

    for (int i = 1; i < argc; i++) {
        
        char *arg = argv[i];
 
        if (isdigit(*arg) || 
            (*arg == '-' && isdigit(arg[1])) || // -5, -3.14 etc.
            (*arg == '+' && isdigit(arg[1])) || // +5
            (*arg == '.' && isdigit(arg[1]))) { // .5 (but not -.5 or +.5 use --> -0.5 or +0.5 instead)
            push(atof(arg));
        } 
        else if (strlen(arg) == 1) {
            switch (arg[0]) {
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
                    if (op2 != 0.0) {
                        push(pop() / op2);
                    }
                    else 
                        printf("error: zero divisor\n");
                    break;
                default:
                    printf("error: unknown command %s\n", arg);
                    break;            
            }
        }
    }

    // Final result
    if (sp == 1)
        printf("%g\n", pop());
    else if (sp > 1) 
        printf("error: %d items left on stack\n", sp);
    else 
        printf("Stack is empty\n");

return 0;
}



