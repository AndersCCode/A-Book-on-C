/* Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing.
Good possibilities include getline (Chapter 1 and 4), atoi, itoa, and their variants (Chapter 2, 3 and 4), 
reverse (Chapter 3), and strindex and getop (Chapter 4). */

#include <stdio.h>

/* Convert s to integer */
int atoi(const char *s)
{
    int n = 0;
    int sign = 1;   // assume positive

    while (*s == ' ' || *s == '\t' || *s == '\n')
        s++;

    sign = (*s == '-') ? -1 : 1;
    
    if (*s == '+' || *s == '-')        // skip sign
        s++;

    while (*s >= '0' && *s <= '9'){
        n = 10 * n + (*s++ - '0');
    }

    return sign * n;
}

int main(void) 
{
    printf("%d\n", atoi("6"));
    printf("%d\n", atoi("+6"));
    printf("%d\n", atoi("-1"));
    printf("%d\n", atoi("-123"));
    printf("%d\n", atoi("    -3"));
    printf("%d\n", atoi("+"));
    printf("%d\n", atoi("-"));
    printf("%d\n", atoi(" abc"));

    return 0;
}