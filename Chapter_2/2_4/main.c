/* Write an alternative version of squeeze(s1, s2) that deletes
each character in s1 that matches any character in the string s2. */

#include <stdio.h>

void squeeze(char s1[], char s2[]) {
    char temp[100];
    int k = 0;
    
    for (int i = 0; s1[i] != '\0'; i++) {
        int character_present = 0;

        for (int j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                character_present = 1;
                break;
            }          
        }

        if (character_present == 0) // Character not present in s2 and should be copied to temp
            temp[k++] = s1[i];
    }         
    temp[k] = '\0';
    printf("s1: %s\nCharacters to remove: %s\nCharacters only present in s1: %s\n", s1, s2, temp);
}

int main(void) {
    char s[] = "abcdefghj";
    char remove[] = "cde"; 
    squeeze(s, remove);
return 0;
}