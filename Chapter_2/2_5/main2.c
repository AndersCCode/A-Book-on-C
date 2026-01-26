/* Write the function any(s1,s2), which returns the first location in the string s1 where any character from string s2
occurs, or -1 if s1 contains no characters from s2. (The standard library function strpbrk does the same job but returns
a pointer to the location.)*/

#include <stdio.h>

int any(const char s1[], const char s2[]) {
    
    for (int i = 0; s1[i] != '\0'; i++) {
        for (int j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j]) 
                return i;          
    }
    return -1;  // No match found in s2       
}

int main(void) {
    char base[] = "hello world";
    char duplicates[] = "o"; 
    
    int pos = any(base, duplicates);
    
    if (pos >= 0) 
        printf("First match at position %d\n", pos);
    else printf("No characters from s2 found in s1\n");

return 0;
}