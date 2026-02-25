/* Write the function itob(n,s,b) that converts the integer n into a base b character 
representation in the string s. In particular, itob(n,s,16) formats n as a 
hexadecimal integer in s.*/

#include <stdio.h>
#include <string.h> 

void reverse(char s[])
{
    int i, j;
    char temp;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

/* itob: convert n to base-b character representation in s */
void itob(int n, char s[], int b)
{
    int i = 0;
    int sign = 1;
    unsigned int un = n;   /* handles negative numbers cleanly */

    /* Reasonable base check (exercise doesn't require it, but it's good practice) */
    if (b < 2 || b > 36) {
        s[0] = '\0';
        return;
    }

    if (n < 0) {
        sign = -1;
        un = -n;               /* works even for INT_MIN on two's-complement */
    }

    /* Generate digits (least significant first) */
    do {
        int digit = un % b;
        s[i++] = (digit < 10) ? digit + '0' : digit - 10 + 'A';  /* A-F for hex */
        un /= b;
    } while (un > 0);

    /* Add sign if needed */
    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';

    reverse(s);   
}

int main(void)
{
    char converted[32];   /* plenty of room */

    itob(12, converted, 16);
    printf("12 in hex     = %s\n", converted);   /* → C */

    itob(255, converted, 16);
    printf("255 in hex    = %s\n", converted);   /* → FF */

    itob(42, converted, 2);
    printf("42 in binary  = %s\n", converted);   /* → 101010 */

    itob(-123, converted, 10);
    printf("-123 in dec   = %s\n", converted);   /* → -123 */

    itob(0, converted, 16);
    printf("0 in hex      = %s\n", converted);   /* → 0 */

    return 0;
}
