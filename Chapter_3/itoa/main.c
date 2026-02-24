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
    int i, sign;

    if ((sign = n < 0))
        n = -n;             // make n positive

    i = 0;

    do {
        s[i++] = n % 10 + '0';  // Get next digit
    } while ((n /= 10) > 0);    // delete it

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';

    /* === DEMO: see the raw characters === */
    printf("Internal before reverse. n = %d:\n", n);  // note: n is now 0 here
    for (int k = 0; s[k] != '\0'; k++)
        printf("  s[%d] = %3d '%c'\n", k, s[k], s[k]);
    /* ================================== */

    reverse(s);
}

int main(void) {

    char buffer[32];

    printf("itoa test:\n");
    printf("==========\n");
    
    itoa(82, buffer);
    printf("  82   -->  '%s'\n", buffer);

    itoa(95, buffer);
    printf("  95   -->  '%s'\n", buffer);

    itoa(115, buffer);
    printf(" 115   -->  '%s'\n", buffer);
    
    itoa(-42, buffer);
    printf(" -42   -->  '%s'\n", buffer);
    
    itoa(0, buffer);
    printf("   0   -->  '%s'\n", buffer);

    return 0;
}