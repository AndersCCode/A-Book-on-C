/* gcc -Wextra -Wall -o2 -o reverse main.c */

#include <stdio.h>

void reverse(char *s) {
    if (*s == '\0') {
        printf("Empty string\n");
        return;
    }

    char *start = s;
    char *end = s;
    
    // Find end (will point at \0)
    while (*end!= '\0') {
        end++;
    }    
    
    while (end >= start) {
        printf("%c", *end);
        end--;    
    }
    printf("\n");
}

int main(void) {
    
    reverse("");
    reverse("a");
    reverse("even");
    reverse("odd");

return 0;
}