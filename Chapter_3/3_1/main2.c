#include <stdio.h>

#define MAX 3

int binsearch(int x, int v[], int n) {
    int low, mid, high; // index

    low = 0;
    high = n - 1;

  

    while (low <= high) {   
        mid = (low+high) / 2;   
        
        if (x <= v[mid]) 
            high = mid -1;
        else 
            low = mid + 1;
    } 
    
    if (low < n && v[low] == x)
        return low;
    else
        return -1; // No match
}

int main(void) {

    int v[MAX];
    int x = 11;
    int val = 0;

    // Populate array
    v[0] = 3;
    v[1] = 5;
    v[2] = 7;
    
    /*for (int i = 0; i < MAX; i++) {
        v[i] = i + 2;
        printf("v[%d] = %d\n", i, v[i]);
    }*/

    val = binsearch(x, v, MAX);
    (val > -1) ? printf("%d is on position %d\n", x, val) : printf("%d not found\n", x);
    return 0;
}