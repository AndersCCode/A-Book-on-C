/* A union is like a structure but all of the elements of the union overlap and allow
you to view the same area of memory as multiple types. */

#include <stdio.h>
#include <string.h>

int main(void) {
    
    union sample {
        int i;
        char ca[4];
        float f;
    };

    union sample u;
    
    u.i = 42;
    printf("%08x %f %s\n", u.i, u.f, u.ca);

    strcpy(u.ca, "Abc");
    printf("%08x %f %s\n", u.i, u.f, u.ca);

    u.f = 1.0/3.0;
    printf("%08x %f %s\n", u.i, u.f, u.ca);

return 0;
}