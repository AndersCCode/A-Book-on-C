/* Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s, 
and zero otherwise */

#include <stdio.h>

#define MAXLEN 100

int strend(char *s, char *t) {

    const char *s_end = s;
    const char *t_end = t;

    /* find end of s */
    while (*s_end != '\0')                
        s_end++;

    /* find end of t */
    while (*t_end != '\0')                
        t_end++;
    
    /* Compare */
    while (t_end > t) {
        if (s_end == s || *--s_end != *--t_end) {
            return 0;
        }
    }
    
    return 1; 
}

int main(void) {
    
    char base[MAXLEN] = "abc";
    char search[MAXLEN] = "bc";
    
    if (strend(base, search) > 0) 
        printf("%s is in %s\n", search, base);
    else 
        printf("%s is not present in %s\n", search, base);

    return 0;
}

