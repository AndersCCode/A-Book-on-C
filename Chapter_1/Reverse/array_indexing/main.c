#include <stdio.h>

void reverse(char *s) {

    int len = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        len++;
    }
    
    if (len == 0) { 
        printf("Empty string\n");
        return;
    }
    else {
        for (int j = len; j >= 0; j--) {
            printf("%c", s[j]);
        }
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