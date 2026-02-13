#include <stdio.h>

void lower(char s[])
{
    int i;

    i = 0;
    while (s[i] != '\0') {
        (s[i] >= 'A' && s[i] <= 'Z') ? s[i] = s[i] + 'a' - 'A' : s[i]; // When false just read
        i++;
    }
}

int main(void) {
    char s[] = "ABC";
    lower(s);

    printf("%s\n", s);
}