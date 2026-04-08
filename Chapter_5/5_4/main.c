/* Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s, 
and zero otherwise */

#include <stdio.h>

#define MAXLEN 100

int strend(char *s, char *t) {

    /* find end of s */
    while (*s != '\0')                
        s++;

    /* find end of t */
    while (*t != '\0')                
        t++;
    
    /* Compare */
    while (*s-- == *t-- && t != NULL) {
        ;
    }
    if (t == NULL) {
        return 1;
    } else return 0; 
}

int main(void) {
    
    char base[MAXLEN] = "abc";
    char search[MAXLEN] = "bc";
    
    if (strend(base, search) > 0) {
        printf("%s is in %s\n", search, base);
    } else printf("%s is not present in %s\n", search, base);

    return 0;
}

