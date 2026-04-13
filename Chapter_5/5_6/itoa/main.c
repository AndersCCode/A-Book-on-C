/* Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing.
Good possibilities include getline (Chapter 1 and 4), atoi, itoa, and their variants (Chapter 2, 3 and 4), 
reverse (Chapter 3), and strindex and getop (Chapter 4). */

#include <stdio.h>

#define MAXLINE 1000

/* reverse string s in place */
void reverse(char *s) {

    char *start = s;
    char *end = s;
    char temp;


    // find end of s 
    while (*end)                
        end++;

    // Back off from '\0'
    if (end > s)        // avoid empty string
        end--;

    while (start < end) {
        temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
}

/* convert n to characters in s */
void itoa(int n, char *s) 
{
    int sign = 1;       // assume positive
    char *p = s;        // p will walk through the string

    if ((sign = n) < 0)
        n = -n;

    do {                                // generate digits in reverse order
        *p++ = (n % 10) + '0';              // get the next digit
    } while ((n /= 10) > 0);            // delete it

    if (sign < 0)
        *p++ = '-';

    *p = '\0';      // terminate

    printf("In itoa (before reverse): %s\n", s);

    reverse(s);     // put back in right order
}

int main(void) 
{
    char s[MAXLINE]; 

    itoa(123, s);
    printf("After itoa(123): %s\n", s);

    itoa(-4567, s);
    printf("After itoa(-4567): %s\n", s);

    itoa(0, s);
    printf("After itoa(0): %s\n", s);

    return 0;
}