/* Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, 
leaving the other bits unchanged. */

#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y)  {

    printf("x = 0x%02X 0b%08b\n",  x, x);
    printf("y = 0x%02X 0b%08b\n",  y, y);
    printf("p = %d n = %d\n", p, n);

    // 1. Create mask with n ones in the rightmost positions:   00000111  (for n=3)
    unsigned mask = ~(~0u << n);          
    printf("mask = 0x%02X 0b%08b\n",  mask, mask);
    
    // 2. Extract the rightmost n bits from y
    unsigned bits_from_y = y & mask;     // 0000 0111 & 0000 0111
    printf("bits from y = 0x%02X 0b%08b\n",  bits_from_y, bits_from_y);

    // 3. Shift those bits left so they land at position p
    // We need to move them left by (p - n + 1) positions
    unsigned shifted = bits_from_y << (p - n + 1);
    printf("shifted = 0x%02X 0b%08b\n",  shifted, shifted);

    // 4. Create mask with 0s exactly where we want to insert (positions p down to p-n+1)
    //    First create ones in the field, then invert
    unsigned field_mask = mask << (p - n + 1);   // 00000111 << 3 = 00111000
    unsigned clear_mask = ~field_mask;           // 11000111
    printf("field mask = 0x%02X 0b%08b\n", field_mask, field_mask);
    printf("clear mask = 0x%02X 0b%08b\n", clear_mask & 0xFF, clear_mask & 0xFF);

    // 5. Clear the target bits in x, then OR in the new bits
    unsigned cleared_x = x & clear_mask;
    printf("cleared x = 0x%02X 0b%08b\n", cleared_x, cleared_x);
    return cleared_x | shifted;
    }

int main(void) {
    unsigned x = 0x4C;  // 0100 1100
    unsigned y = 0x07;  // 0000 0111
    unsigned result;    // 0111 1100 0x7C

    result = setbits(x,7,4,y);

    printf("\n\nResult: 0x%02X binary: %08b\n", result, result);

    /*unsigned mask_right = ~(~0u << 3);
    printf("0u = 0x%02X 0b%08b\n", 0u, 0u); // Unsigned int är 32-bitar på denna plattform (Linux). Alla 0:or kommer inte att visas
    printf("~0u = 0x%02X 0b%08b\n", ~0u, ~0u);
    printf("~0u << 3 = 0x%02X 0b%08b\n", ~0u << 3, ~0u << 3);
    printf("~(~0u << 3) = 0x%02X 0b%08b\n", ~(~0u << 3), ~(~0u << 3));*/

    return 0;
}