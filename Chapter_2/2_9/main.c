/* Counts the number of 1-bits in x 
A 32-bit wordlength requires 32 iterations. Could this be done faster? 
Yes, see main.c */

#include <stdio.h>

unsigned bitcount(unsigned x)  {
    int count = 0;
    int n = 0; // debug
    
    while (x) {
        x &= (x - 1);
        printf("1-bit%d\n", n); // debug
        n++; // debug
        count++;
    }
    return count;
}

int main(void) {
    unsigned x = 0xC0000003;  // 1100 0000 ... 0000 0011
    unsigned result;    

    int word_size = sizeof(unsigned) * 8;
    printf("\nWordsize = %d\n\n", word_size);

    result = bitcount(x);   
    printf("\nx = 0x%08X 0b%032b contains %d 1-bits\n\n", x, x, result);

    return 0;
}