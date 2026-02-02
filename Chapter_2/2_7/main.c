/* Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted
(i.e., 1 changed into 0 and vice versa), leaving the others unchanged. */

#include <stdio.h>

unsigned invert(unsigned x, int p, int n)  {
    
    printf("x = 0x%02X 0b%08b\n",  x, x);
    printf("p = %d n = %d\n", p, n);

    // 1. Create mask n wide
    unsigned mask = ~(~0u << n);          
    printf("mask = 0x%02X 0b%08b\n",  mask, mask);

    // 2. Create mask with 1s exactly where we want to invert (positions p down to p-n+1)
    unsigned field_mask = mask << (p - n + 1);   // Shift to position p
    printf("field mask = 0x%02X 0b%08b\n", field_mask, field_mask & 0xFF);
    return x ^ field_mask;
    }

int main(void) {
    unsigned x = 0x4C;  // 0100 1100
    unsigned result;    

    result = invert(x,6,4);

    printf("\n\nResult: 0x%02X binary: %08b\n\n", result, result);

    return 0;
}