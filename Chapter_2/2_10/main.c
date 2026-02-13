#include <stdio.h>

int main(void) {
    int n = 100;
    int a[n];

    for (int i = 0; i < n; i++)
        a[i] = i;

    for (int j = 0; j < n; j++)
        printf("%6d%c", a[j], (j%10==9 || j==n-1) ? '\n' : ' '); // Does j end with 9 ? 
return 0;
}