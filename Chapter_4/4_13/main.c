/* Write a recursive version of the function reverse(s), which reverses
the string s n place */

#include <stdio.h>

/* reverse: reverse string s in place (recursive) */
void reverse(char s[])
{
    static int i = 0;        
    static int j;            

    if (s[i] == '\0') {      // reached the end
        j = i - 1;           // j now points to last character 
        i = 0;               // reset i for next call (if any)
        return;
    }

    i++;                     // move to next character 
    reverse(s);              // recurse to the end

    
    if (i < j) {             // only swap if i is still left of j
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++;
        j--;
    }
}

int main(void)
{
    char buffer[32] = "abc";
    reverse(buffer);
    printf("%s\n", buffer);   

    char buffer2[32] = "hello world";
    reverse(buffer2);
    printf("%s\n", buffer2);  

    return 0;
}