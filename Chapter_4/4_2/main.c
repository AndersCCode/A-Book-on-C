/* Extend atof to handle scientific notation of the form 123.45e-6 where a floating-point number may be 
followed by e or E and optionally signed exponent. */

#include <stdio.h>
#include <ctype.h>

// atof: convert string s to double 
double atof(char s[]) {
    double val, power;
    int i, sign;

    /* Skip white space */
    for (i = 0; isspace(s[i]); i++) 
        ;
    
    /* Sign of the number */
    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        i++;

    /* Parse the digits before the decimal point (integer part) */
    for (val = 0.0; isdigit(s[i]); i++) 
        val = 10.0 * val + (s[i] - '0');
    
    /* Skip decimal point */
    if (s[i] == '.') 
        i++;
    
    /* Parse the digits after the decimal point (fractional part) */
    for (power = 1.0; isdigit(s[i]); i++) { 
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    /* Scientific notation */
    if (s[i] == 'e' || s[i] == 'E') {
        i++; // skip e/E
    
        int exp_sign = 1; // default positive exponent
        if (s[i] == '+' || s[i] == '-') {
            exp_sign = (s[i] == '-') ? -1 : 1;
            i++;
        }

        int exponent = 0;
        while (isdigit(s[i])) { // parse one or more digits
            exponent = 10 * exponent + (s[i] - '0');
            i++;
        }

        /* Apply the exponent by shifting val or power */
        if (exp_sign > 0) {
            while (exponent-- > 0) // positive --> make number bigger
                val *= 10.0;
        } else {
            while (exponent-- > 0) // negative --> make number smaller
                val /= 10.0;
        }
    }    
    
    return (sign * val) / power;
}

int main(void) {

    printf("69.420 --> %.6f\n", atof("69.420"));
    printf("123.45e-6 --> %.8f\n", atof("123.45e-6"));
    printf("69.420e-2 --> %.6f\n", atof("69.420e-2"));
    printf("1e10 --> %.0f\n", atof("1e10"));
    printf("-2.5E+3 --> %.0f\n", atof("-2.5E+3"));
    printf("6.022e23 --> %.15g\n", atof("6.022e23"));

    return 0;
}