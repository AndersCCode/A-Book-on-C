/* Write a pointer version of the function strcat that we showed in Chapter 2: strcat(s,t) copies the string t 
to the end of s */

#include <stdio.h>

#define MAXLEN 100

void mystrcat(char *s, char *t) {

    /* find end of s */
    while (*s != '\0')                
        s++;
    
    /* append t */
    while ((*s++ = *t++) != '\0')   
        ;
}

int main(void) {
    
    char original[MAXLEN] = "abc";
    char addendum[MAXLEN] = "def";
    
    printf("Original string: %s\n", original);

    mystrcat(original, addendum);

    printf("Final string: %s\n", original);

    return 0;
}

