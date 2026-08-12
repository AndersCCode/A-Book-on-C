#include <stdio.h>

#define DEBUG

int main(void)
{
    /* preprocessor control lines */
    #if defined(DEBUG)  
        printf("Debug mode is enabled\n");
    #else    
        printf("Debug mode is disabled\n");
    #endif

    /*  identifiers without underscore */
    int count = 0;
    char quote = '"'; // "
    
    /* identifiers with underscore is not a keyword (belonging to the C language) */
    int my_int = 0;
    int _leading = 1;
    int trailing_ = 2;
    int a_b_c = 3;

    /* string literal */
    char string_literal = "a string literal";
    char *path = "c:\\Windows\\System32";
    char *str = "This is a long string \
    that spans float \
    union multiple lines.";
    char ch = 'A';

    /* more comments */
    /* void */
    // return 

    return 0;
}

