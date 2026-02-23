/* atoi: convert s to integer - version 2 */

#include <stdio.h>
#include <ctype.h>

int atoi(char s[]) {
    int i, n, sign;

    for (i = 0; isspace(s[i]); i++) {} // skip white space

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-') // skip sign
        i++;
    
    for (n = 0; isdigit(s[i]); i++) // Convert only digit characters
        n = 10 * n + (s[i] - '0');
    return sign * n;
}

int main(void) {

    char s[] = "  -235 A";

    printf("Result = %d\n", atoi(s));

    return 0;
}