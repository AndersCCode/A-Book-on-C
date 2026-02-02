/* Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n bit positions */

#include <stdio.h>

unsigned rightrot(unsigned x, int n)  {

    printf("n = %d\n",  n);
    
    int word_size = sizeof(unsigned) * 8;
    printf("wordsize = %d\n", word_size);
    
    // Debug
    /*printf("\n1u = 0x%08X 0b%032b\n", 1u, 1u);
    printf("1u << n = 0x%08X 0b%032b\n", 1u << n, 1u << n);
    printf("(1u << n) - 1u = 0x%08X 0b%032b\n", ((1u << n) - 1u), ((1u << n) - 1u));
    printf("x & ((1u << n) - 1u) = 0x%08X 0b%032b\n\n", x & ((1u << n) - 1u), x & ((1u << n) - 1u));
    
    printf("0u = 0x%08X 0b%032b\n", 0u, 0u);
    printf("~0u = 0x%08X 0b%032b\n", ~0u, ~0u);
    printf("~0u << n = 0x%08X 0b%032b\n", ~0u << n, ~0u << n);
    printf("~(~0u << n) = 0x%08X 0b%032b\n", ~(~0u << n), ~(~0u << n));
    printf("x & (~(~0u << n)) = 0x%08X 0b%032b\n", x & (~(~0u << n)), x & (~(~0u << n)));*/

    // Rightmost n bits
    unsigned right_bits = x & (~(~0u << n));
    printf("\nrighmost bits = 0x%08X 0b%032b\n", right_bits, right_bits);
    
     // Shift rightmost bit to the left 
    unsigned moved_to_left = right_bits << (word_size - n); 
    printf("moved to the left = 0x%08X 0b%032b\n", moved_to_left, moved_to_left);
    
    // Shift the rest of x right
    unsigned shifted = x >> n;
    printf("x shifted to the right = 0x%08X 0b%032b\n", shifted, shifted);

    // Combine
    return shifted | moved_to_left;
    }

int main(void) {
    unsigned x = 0xC0000003;  // 1100 0000 ... 0000 0011
    unsigned result;    

    printf("\nx = 0x%08X 0b%032b\n",  x, x);

    result = rightrot(x,2);   
    printf("\nResult: 0x%08X binary: %032b\n\n", result, result);

    return 0;
}