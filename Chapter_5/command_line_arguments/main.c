/* This is the first version of echo command-line arguments. 
It treats argv as an array of character pointers. */

#include <stdio.h>

int main(int argc, char *argv[]) {
    int i;

    for (i = 1; i < argc; i++)  // starts at 1, skips program name
        printf("%s%s", argv[i], (i < argc - 1) ? " " : "");
    printf("\n");

return 0;
}