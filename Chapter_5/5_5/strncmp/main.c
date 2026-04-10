/* Write versions of the library functions strncpy, strncat and strncmp, which operate on at most 
the first n characters of their argument strings. For example, strncpy(s,t,n) copies at most n 
characters of t to s. Full descriptions are in Appendix B. */

#include <stdio.h>

#define MAXLEN 100

int a_strncmp(char *s, const char *t, size_t n) {
    const char *s_start = s;
    const char *t_start = t;

     /* find end of s */
    while (*s)                
        s++;

    /* append n charachters to s */    
    while (n > 0 && *t != '\0') {
        *s++ = *t++;
        n--;
    }
    *s = '\0';      /* Terminate */

    return s_start;

    /* Compare */
    while (*s != '\0' && *t != '\0' && n > 0) { /* As long as t_end is bigger than the start (as long as there is characters to compare)*/
        if (*--s != *--t) {  /* s_end == s Have we compared all characters in s ? */
            return ;                              /* *--s_end != *--t_end no match */ 
        }
    }
}

int main(void) {

    char x[MAXLEN] = "abc";
    char y[MAXLEN] = "abc";

    int res = a_strncmp(goal, source, 2);

    if (res == 0) 
        printf("x = y\n");
    else if (res <0)
        printf("x < y\n");
    else printf("x > y\n");

    return 0;
}