// Counts digits, white spaces ond others.
// Press Ctrl-D to present the results.

#include <stdio.h>

int main(void) {
    int c, i, nwhite, nother, ndigit[10];

    nwhite = nother = 0;
    for (i = 0; i < 10; i++)
        ndigit[i] = 0;

    while ((c = getchar()) != EOF) {
        switch (c) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': 
            ndigit[c-'0']++;
            break;
        case ' ':
        case '\n':
        case '\t': 
            nwhite++;
        default:
            nother++;
            break;
        }
    }
    
    printf("\nDigits:\n");
    for (int k = 0; k < 10; k++) 
        printf(" %2d", k);
    printf("\n");
    for (int l = 0; l < 10; l++) 
        printf(" %2d", ndigit[l]);
    printf("\n\nwhite space = %d\nother = %d\n", nwhite, nother);

    return 0;
}