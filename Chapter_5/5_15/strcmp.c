#include <stdio.h>
#include <string.h>

int main(){
    char* s1 = "Geeks"; // G = 71
    char* s2 = "geeks"; // g = 103

    // Printing the return value of the strcmp()
    printf("%d\n", strcmp(s1, s2));

    printf("%d\n", strcasecmp(s1, s2));     // case-insensitive string compare 

    return 0;
}