/* Write a program to print all input lines that are longer than 
80 charachters. */

#include <stdio.h>

#define MAXLINE 1000
#define LONGLINE 80

int mygetline(char s[], int lim) {
    int c, i = 0;
    
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    
        if (c == '\n') 
    s[i++] = '\n';
    
    s[i] = '\0';
    
    return i;
}

int main() {
    char line[MAXLINE];
    int len;

    while ((len = mygetline(line, MAXLINE)) > 0) {
        if (len > LONGLINE) {
            printf("%s", line);
        }
    }
    return 0;
}