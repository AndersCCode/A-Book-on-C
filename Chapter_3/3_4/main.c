/* In a two's complement number representation, our version of itoa doesn't handle the largest
negative number, that is, the value of n equal to -(2^wordsize-1). Explain why not. 
Modify it to print that value correctly regardless of the machine on which it runs. 

The line n = -n has a flaw. You can't safely do n = -n (or -n) when n is the most 
negative signed value. It could cause overflow.

if ((sign = n < 0))
    n = -n;     

INT_MIN = -2^31 = -2147483648
INT_MAX = 2^31-1 = 2147483647

INT_MIN = -(INT_MAX+1)

n = -n tries to compute 2147483648, which is 1 larger than INT_MAX --> signed integer 
overflow. In C, signed overflow is undefined behavior (the program may crash, give wrong 
output, loop forever etc.).

*/

#include <stdio.h>
#include <string.h>

void reverse(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[]) {
    int i = 0;
    int sign = n;
    unsigned int u;

    /* Convert to unsigned absolute value - this works even for INT_MIN */
    u = (n < 0) ? -(unsigned int)n : (unsigned int)n;

    do {
        s[i++] = u % 10 + '0';  // Get next digit
    } while ((u /= 10) > 0);    // delete it

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';

    /* === DEMO: see the raw characters === */
    //printf("Internal before reverse. n = %d:\n", n);  // note: n is now 0 here
    //for (int k = 0; s[k] != '\0'; k++)
    //    printf("  s[%d] = %3d '%c'\n", k, s[k], s[k]);
    /* ================================== */

    reverse(s);
}

int main(void) {

    char buffer[32];

    printf("itoa test:\n");
    printf("==========\n");
    
    itoa(-2147483648, buffer);   /* the problematic value */
    printf("INT_MIN = %s\n", buffer);
    
    itoa(2147483647, buffer);   /* the problematic value */
    printf("INT_MIN = %s\n", buffer);

    itoa(0, buffer);
    printf("0 = %s\n", buffer);

    itoa(123, buffer);
    printf("123 = %s\n", buffer);

    return 0;
}