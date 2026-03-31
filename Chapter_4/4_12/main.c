#include <stdio.h>
#include <stdlib.h>

void itoa(int n, char s[]) {
    static int i;           // position to the sting; persists across recursive calls 

    if (n / 10)             // as long as n / 10 > 1 (more digits left)
        itoa(n / 10, s);    // recurse on the higher digits first
    else {                  // base case: we've reached the highest digit
        i = 0;              // reset index 
        if (n < 0)
            s[i++] = '-';
    }

    s[i++] = abs(n) % 10 + '0'; // place current digit
    s[i] = '\0';                // temporarily terminate; will be overwritten on unwind 
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