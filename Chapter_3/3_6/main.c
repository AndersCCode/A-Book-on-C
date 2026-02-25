/* Write a version of itoa that accepts three arguments instead of two. The third argument
is a minimum field with; the converted number must be padded with blanks on the left if 
necessary to make it wide enough. */

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
void itoa(int n, char s[], int w) {
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

    while (i < w)
        s[i++] = ' ';
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

    printf("\nitoa test:\n");
    printf("==========================\n");
    
    itoa(-2147483648, buffer, 15);   
    printf("INT_MIN = %s\n", buffer);
    
    itoa(2147483647, buffer, 15);  
    printf("INT_MAX = %s\n", buffer);

    itoa(0, buffer, 15);
    printf("      0 = %s\n", buffer);

    itoa(123, buffer, 15);
    printf("    123 = %s\n\n", buffer);

    return 0;
}