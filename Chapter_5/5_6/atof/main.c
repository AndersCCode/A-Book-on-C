/* Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing.
Good possibilities include getline (Chapter 1 and 4), atoi, itoa, and their variants (Chapter 2, 3 and 4), 
reverse (Chapter 3), and strindex and getop (Chapter 4). */

#include <stdio.h>

/* Convert s to float */
double atof(const char *s)
{
    double val = 0.0;
    double power = 1.0;
    int sign = 1;           // assume positive

    // ignore white spaces
    while (*s == ' ' || *s == '\t' || *s == '\n')
        s++;

    sign = (*s == '-') ? -1 : 1;
    
    if (*s == '+' || *s == '-')        // skip sign
        s++;

    // read integer part
    while (*s >= '0' && *s <= '9') {
        val = 10.0 * val + (*s++ - '0');
    }

    if (*s == '.')  // skip .
        s++;

    // read decimal part
    while (*s >= '0' && *s <= '9') {
        val = 10.0 * val + (*s++ - '0');
        power *= 10.0;
    }
    return sign * (val / power);
}

int main(void) 
{
    printf("%g\n", atof("6.0"));
    printf("%g\n", atof("+6.0"));
    printf("%g\n", atof("-1.0"));
    printf("%g\n", atof("-123.5"));
    printf("%g\n", atof("    -3.7"));
    printf("%g\n", atof("+"));
    printf("%g\n", atof("-"));
    printf("%g\n", atof(" abc"));

    return 0;
}