#include <stdio.h>
#include <ctype.h>  // for tolower() — optional but makes life easier

/* Converts hexadecimal string to integer
   Accepts: 0x1a3f, 0Xff, 7b4, aBc, etc.
   Returns: the integer value
*/
int htoi(const char s[])
{
    int i = 0;
    int value = 0;

    // Skip optional 0x or 0X prefix
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        i = 2;

    while (s[i] != '\0')
    {
        char c = s[i];
        
        if (c >= '0' && c <= '9')
            value = value * 16 + (c - '0');
        else if (c >= 'a' && c <= 'f')
            value = value * 16 + (c - 'a' + 10);
        else if (c >= 'A' && c <= 'F')
            value = value * 16 + (c - 'A' + 10);
        else
            break;   // stop at first invalid character

        i++;
    }

    return value;
}

int main(void) {
    printf("0x1a3f eqauals to %d decimal\n", htoi("1a3f"));
    printf("0xFF eqauals to %d decimal\n", htoi("0xFF"));
    printf("0x7B4 eqauals to %d decimal\n", htoi("7B4"));
    printf("0x7B6 eqauals to %d decimal\n", htoi("7B6"));
    printf("deadbeef eqauals to %d decimal\n", htoi("deadbeef"));    
    printf("0x0A eqauals to %d decimal\n", htoi("0x0A"));
    printf("0xBF eqauals to %d decimal\n", htoi("0xBF"));  
}