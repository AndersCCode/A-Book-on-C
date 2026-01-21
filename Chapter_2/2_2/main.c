#include <stdio.h>

int main(void) {
       
    int lim = 100;
    char s[lim];
    int c;
 
    //for (int i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i) {
    //    s[i] = c;
    //}

// Write a loop equivalent to the for loop above without using && or ||

    int i=0;

    while (i < lim - 1) {
        c=getchar();
        if (c == '\n') 
            break;
        if (c == EOF) 
            break;
        s[i] = c;
        i++;
    }
    s[i] = '\0';
}


    
