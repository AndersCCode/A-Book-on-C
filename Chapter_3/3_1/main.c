#include <stdio.h>

#define MAX 10

int binsearch(int x, int v[], int n) {
    int low, mid, high; // index

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid -1;
        else if (x > v[mid])
            low = mid + 1;
        else 
            return mid;
    }
    return -1; // No match
}

int main(void) {

    int v[MAX];
    int x = 77;
    int val = 0;

    for (int i = 0; i < MAX; i++) {
        v[i] = i + 2;
        printf("v[%d] = %d\n", i, v[i]);
    }

    // printf("Position %d\n", binsearch(x, v, MAX));
    val = binsearch(x, v, MAX);
    (val > -1) ? printf("%d is on position %d\n", x, val) : printf("%d not found\n", x);
    return 0;
}