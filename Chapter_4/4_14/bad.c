/* Define a macro swap(t,x,y) that interchanges two arguments of type t.
Block structure will help */

#include <stdio.h>

/*  _temp to reduce risk of name clash with user variables 
    #define swap(t, x, y) do { t _temp = (x); (x) = (y); (y) = _temp; } while (0) 
    Leaving out do while will create syntax problem for if else (see below).    
*/


#define swap(t, x, y) { t _temp = (x); (x) = (y); (y) = _temp; } 

int main(void) {
    
    int a = 10, b = 20;

    if (a < b)
        swap(int, a, b);
    else
        printf("No swap\n");

    printf("After: a=%d b=%d\n", a, b);
    
    return 0;
}