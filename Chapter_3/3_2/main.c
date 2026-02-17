/* 1. Write a function escape(s,t) that converts characters like
newline and tab into visible escape sequences like \n and \t as it copies the string t to s.
Use a switch. 

2. Write a function for the other direction as well, 
converting escape sequences into the real characters.*/
#include <stdio.h>

void escape(char s[], const char t[]) {
    for (int i = 0; t[i] != '\0'; i++) {  
        switch (t[i]) {
        case '\n':
            s[i] = t[i];
            printf("Newline\n");
            break; 
        case '\t':
            printf("Tab \n");
            break;
        default:
            break;
        }
    }     
}

int main(void) {
    char s[] = "";
    char t[] = "Hello \n \t";
    escape(s, t);
    printf("s = %s\n", s);
    printf("t = %s\n", t);
        

    return 0;
}