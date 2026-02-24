/* Write a function expand(s1, s2) that expands shorthand notatiions like a-z
in the string s1 into the equivalent complete list abc...xyz in s2.
Allow for letters of either case and digits, and be prepared to handle cases 
like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is 
taken literally.*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void expand(const char s1[], char s2[]) {
    int i = 0, j = 0;

    while (s1[i] != '\0') {
        // Is this a - followed by at least one character?
        if (s1[i+1] == '-' && s1[i+2] != '\0') {
            char start = s1[i];
            char end = s1[i+2];

            if (start <= end && 
                ((islower(start) && islower(end)) ||
                (isupper(start) && isupper(end)) ||
                (isdigit(start) && isdigit(end)))) {
                
                for (char c = start; c <= end; c++) {
                        s2[j++] = c;
                }
                i += 2; // skip over the '-' and the end char
            }
            else {
                s2[j++] = s1[i]; // Invalid range i.e. z-a, A-z, 1-3
            }
        }
        else {
            s2[j++] = s1[i]; // Invalid syntax. Just copy the character.
        }
        i++;
    }
    s2[j] = '\0';
}

int main(void) {

    char tests[][50] = {
        "a-c", // abc
         "-a-z", // abcdefghijklmnopqrstuvxyz
         "a-z-", // abcdefghijklmnopqrstuvxyz-
         "a-b-c", // ab-c
         "0-9", // 0123456789
         "a-z0-9", //abcdefghijklmnopqrstuvxyz0123456789
         "z-a", // z-a
         "A-Z", // ABCDEFGHIJKLMNOPQRSTUVXYZ
         "a--b" // a--b
    };

    int num_tests = sizeof(tests) / sizeof(tests[0]);
    
    char result[200];

    for (int t = 0; t < num_tests; t++) {
        
        expand(tests[t], result);

        printf("'%s' --> '%s'\n", tests[t], result);
    }
    return 0;
}