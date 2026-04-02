/* Define a macro swap(t,x,y) that interchanges two arguments of type t.
Block structure will help */

#include <stdio.h>

/* _temp to reduce risk of name clash with user variables
do while executes only one time (false on first evaluation)
() protects against side effects and operator precedence problems
 and also improve readability and clarity */


#define swap(t, x, y) do { t _temp = (x); (x) = (y); (y) = _temp; } while (0) 

int main(void) {
    
    int a = 10, b = 20;

    printf("Before: a=%d b=%d\n", a, b);
    swap(int, a, b);
    printf("After: a=%d b=%d\n", a, b);

    double x = 1.5, y = 3.7;

    printf("Before: x=%f y=%f\n", x, y);
    swap(float, x, y);
    printf("After: x=%f y=%f\n", x, y);

    return 0;
}