/* Write versions of the library functions strncpy, strncat and strncmp, which operate on at most 
the first n characters of their argument strings. For example, strncpy(s,t,n) copies at most n 
characters of t to s. Full descriptions are in Appendix B. */

#include <stdio.h>

#define MAXLEN 100

char * a_strncpy(char *s, const char *t, size_t n) {
    
    char *s_start = s;

    /* copy characters */
    while (n > 0 && *t != '\0') {   
        *s++ = *t++;
        n--;
    }
    *s = '\0';      /* Terminate */

    return s_start;
}

int main(void) {

    char goal[MAXLEN] = "";
    char source[MAXLEN] = "abc";

    printf("strncpy after: %s\n", a_strncpy(goal, source, 2));

    return 0;
}