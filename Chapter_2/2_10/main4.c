#include <stdio.h>

void lower(char s[])
{
    for (int i = 0; s[i] != '\0'; i++)
        (s[i] >= 'A' && s[i] <= 'Z') ? s[i] = s[i] + 'a' - 'A' : s[i]; // When false just read
}

int main(void) {
    char s[] = "ABC";
    lower(s);

    printf("%s\n", s);
}