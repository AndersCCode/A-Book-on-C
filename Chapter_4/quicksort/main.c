#include <stdio.h>
#define MAXLEN 3

void swap(int v[], int i, int j) {
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
/* Left is starting index, right is ending index. 
*/
void qsort(int v[], int left, int right) {
    int i, last;

    // Do nothting if arrary contains fewer than two elements
    if (left >= right)
        return;

     // Move partition element to v[0]
    swap(v, left, (left + right)/2);
    last = left;

    for (i = left+1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    
        swap(v, left, last);        // restore partition element
        qsort(v, left, last-1);
        qsort(v, last+1, right);
}

int main(void) {

    int test[MAXLEN] = {5, 3, 1};

    qsort(test, 0, MAXLEN-1);

    for (int i = 0; i < MAXLEN; i++)
        printf("%d", test[i]);
    
    return 0;

}