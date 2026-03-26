#include <stdio.h>

void printd(int n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n /10);
    putchar(n % 10 + '0');
}

int main(void) {
    printd(123);
    printf("\n%d\n", 123 / 10);
    printf("%d\n", 123 % 10);
    printf("%d\n", 1 % 10);

    return 0;
}