/* Write a function expand(s1, s2) that expands shorthand notatiions like a-z
in the string s1 into the equivalent complete list abc...xyz in s2.
Allow for letters of either case and digits, and be prepared to handle cases 
like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is 
taken literally.*/

#include <stdio.h>

void expand(char s1[], char s2[]) {
    
}

int main(void) {

    char source[] = "a-z";
    char destination[] = 200;
    
    expand(source, destination);

    printf("Source = %s\n Destination = %s\n", source, destination);

    return 0;
}