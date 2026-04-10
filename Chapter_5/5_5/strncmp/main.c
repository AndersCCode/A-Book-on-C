/* Write versions of the library functions strncpy, strncat and strncmp, which operate on at most 
the first n characters of their argument strings. For example, strncpy(s,t,n) copies at most n 
characters of t to s. Full descriptions are in Appendix B. */

#include <stdio.h>

#define MAXLEN 100

int a_strncmp(const char *s, const char *t, size_t n) {

    // compare n charachters to s   
    while (n > 0 && *s != '\0' && *t != '\0') {     // Alternative version: while (n > 0 && *s && *t)
        if (*s != *t)
            return *s - *t;
        
        s++;
        t++;
        n--;
    }

    // If we get here, either n reached 0 or one string ended
    if (n == 0)                  // Compared all characters, all equal 
        return 0;               

    return *s - *t;             // One string ended, the other didn't
}

int main(void) {

    char x[MAXLEN] = "abc";
    char y[MAXLEN] = "abc";

    int res = a_strncmp(x, y, 5);

    if (res == 0) 
        printf("x = y\n");
    else if (res < 0)
        printf("x < y\n");
    else printf("x > y\n");

    printf("Result 1: %d\n", a_strncmp("abc", "abd", 3));     
    printf("Result 2: %d\n", a_strncmp("abc", "ab",  4));     
    printf("Result 3: %d\n", a_strncmp("abc", "abcd", 4));    
    printf("Result 4: %d\n", a_strncmp("abc", "abc",  5));    
    printf("Result 5: %d\n", a_strncmp("abc", "abc",  2));    
    printf("Result 6: %d\n", a_strncmp("", "a", 1));          

    return 0;
}