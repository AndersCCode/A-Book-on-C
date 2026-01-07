#include <stdio.h>

int main() {
    int c;

    while (c = getchar() != EOF) {
        putchar(c);
        printf("c at normal input = %d\n", c);
    }
    printf("c at exit (control - d) = %d\n", c);        
}