#include <stdio.h>
#include <limits.h>

int main() {
    printf("On this machine:\n");
    printf("  int ranges from %d to %d\n", INT_MIN, INT_MAX);
    printf("  char has %d bits\n", CHAR_BIT);
    printf("  a float has %d number of decimal digits\n", __FLT_DIG__);
    return 0;
}