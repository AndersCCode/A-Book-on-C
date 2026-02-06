/* Counts the number of 1-bits in x 
A 32-bit wordlength requires 32 iterations. Could this be done faster? 
Yes, see main.c */

#include <stdio.h>

unsigned bitcount(unsigned x)  {
    int b;
    int n = 0; // debug
    
    for (b = 0; x !=0; x >>= 1) {  
        if (x & 01)  // 01 = Octal 1 = 1
            b++;
    printf("Bit%d\n", n); // debug
    n++; // debug
    }
    return b;
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