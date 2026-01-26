#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
    printf("Ranges and sizes on this system:\n\n");

    /* ---------- From standard headers ---------- */
    printf("From <limits.h> and <float.h>:\n\n");

    printf("char is %s\n", CHAR_MIN < 0 ? "signed" : "unsigned");
    printf("  signed char:     %12d to %12d   (%zu bytes)\n", SCHAR_MIN, SCHAR_MAX, sizeof(signed char));
    printf("  unsigned char:   %12d to %12u   (%zu bytes)\n", 0, UCHAR_MAX, sizeof(unsigned char));
    printf("  plain char:      %12d to %12d   (%zu bytes)\n\n", CHAR_MIN, CHAR_MAX, sizeof(char));

    printf("  signed short:    %12d to %12d   (%zu bytes)\n", SHRT_MIN, SHRT_MAX, sizeof(short));
    printf("  unsigned short:  %12d to %12u   (%zu bytes)\n\n", 0, USHRT_MAX, sizeof(unsigned short));

    printf("  signed int:      %12d to %12d   (%zu bytes)\n", INT_MIN, INT_MAX, sizeof(int));
    printf("  unsigned int:    %12d to %12u   (%zu bytes)\n\n", 0, UINT_MAX, sizeof(unsigned int));

    printf("  signed long:     %12ld to %12ld   (%zu bytes)\n", LONG_MIN, LONG_MAX, sizeof(long));
    printf("  unsigned long:   %12d to %12lu   (%zu bytes)\n\n", 0, ULONG_MAX, sizeof(unsigned long));

    printf("  signed long long:%12lld to %12lld   (%zu bytes)\n", LLONG_MIN, LLONG_MAX, sizeof(long long));
    printf("  unsigned long long:%10d to %12llu   (%zu bytes)\n\n", 0, ULLONG_MAX, sizeof(unsigned long long));

    printf("  float:           min ~%e   max ~%e   (%zu bytes)\n", FLT_MIN, FLT_MAX, sizeof(float));
    printf("  double:          min ~%e   max ~%e   (%zu bytes)\n", DBL_MIN, DBL_MAX, sizeof(double));

    /* ---------- Direct computation (integers) ---------- */
    printf("\nComputed directly (assuming two's complement for signed types):\n\n");

    /* unsigned max = all bits 1 */
    unsigned char   uchar_max  = (unsigned char)~0U;
    unsigned short  ushort_max = (unsigned short)~0U;
    unsigned int    uint_max   = ~0U;
    unsigned long   ulong_max  = ~0UL;
    unsigned long long ullong_max = ~0ULL;

    unsigned int test_0U = 0U;
    unsigned int test_tilde0U = ~0U;
    unsigned int test_1U = 1U;   
    unsigned int test_tilde1U = ~1U;
    
    printf("  0U:    %12d to %12u   (%zu bytes)\n\n", 0, test_0U, sizeof(unsigned int));
    printf("  ~0U:    %12d to %12u   (%zu bytes)\n\n", 0, test_tilde0U, sizeof(unsigned int));
    
    printf("  1U:    %12d to %12u   (%zu bytes)\n\n", 0, test_1U, sizeof(unsigned int));
    printf("  ~1U:    %12d to %12u   (%zu bytes)\n\n", 0, test_tilde1U, sizeof(unsigned int));
    
    // printf("  Test unsigned int:    %12d to %12u   (%zu bytes)\n\n", 0, test, sizeof(unsigned int));

    /* signed max = unsigned max >> 1   (arithmetic shift fills with sign bit) */
    signed char   schar_max  = (signed char)( (unsigned char)~0U >> 1 );
    short         short_max  = (short)( (unsigned short)~0U >> 1 );
    int           int_max    = (int)( ~0U >> 1 );
    long          long_max   = (long)( ~0UL >> 1 );
    long long     llong_max  = (long long)( ~0ULL >> 1 );

    /* signed min = - (max + 1) */
    signed char   schar_min  = -schar_max - 1;
    short         short_min  = -short_max - 1;
    int           int_min    = -int_max - 1;
    long          long_min   = -long_max - 1;
    long long     llong_min  = -llong_max - 1;
    
    printf("  unsigned char:   %12d to %12u\n", 0, uchar_max);

    printf("  signed short:    %12d to %12d\n", short_min, short_max);
    printf("  unsigned short:  %12d to %12u\n", 0, ushort_max);

    printf("  signed int:      %12d to %12d\n", int_min, int_max);
    printf("  unsigned int:    %12d to %12u\n", 0, uint_max);

    printf("  signed long:     %12ld to %12ld\n", long_min, long_max);
    printf("  unsigned long:   %12d to %12lu\n", 0, ulong_max);

    printf("  signed long long:%12lld to %12lld\n", llong_min, llong_max);
    printf("  unsigned long long:%10d to %12llu\n", 0, ullong_max);

    printf("\n(Note: Floating-point ranges are reliably obtained only from <float.h>,\n");
    printf("as direct computation requires detailed knowledge of IEEE 754 representation.)\n");

    return 0;
}