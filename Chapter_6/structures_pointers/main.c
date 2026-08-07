#include <stdio.h>

int main(void) {
    struct point {
        double x;
        double y;
    };

    struct point pt, *pp; // pt = regular variable, *pp = pointer to a structure

    pp = &pt;

    pt.x = 3.0;
    (*pp).y = 4.0; // or pp->y = 4.0;

    printf("%p %f %f\n", pp, (*pp).x, pp->y);

    return 0;
}