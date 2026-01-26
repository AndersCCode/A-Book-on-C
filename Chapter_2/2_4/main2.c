/* Write an alternative version of squeeze(s1, s2) that deletes
each character in s1 that matches any character in the string s2. */

#include <stdio.h>

void squeeze(char s1[], char s2[]) {
    int i, j, k = 0;
    char temp[100];
    
    for (i = 0; s1[i] != '\0'; i++) {
        int found = 0;

        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                found = 1;
                break;
            }          
        }

        if (!found) // Character not present in s2 and should be copied to temp
            s1[k++] = s1[i]; // Use the original string but with a special found counter 
    }         
    s1[k] = '\0';
    printf("Characters only present in s1: %s\n", s1);
}

int main(void) {
    char s[] = "abcdefghj";
    char remove[] = "cde"; 
    squeeze(s, remove);
return 0;
}