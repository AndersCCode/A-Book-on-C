#include <stdio.h>
#include <string.h>

void call_by_value(char *local_value) {
    local_value = "changed a local copy";
    printf("Modified in call_by_value: %s\n", local_value);
    
    return;
}

void call_by_reference(char *str) {
    strcpy(str, "new");
    printf("Modified in call_by_reference: %s\n", str);
    
    return;

}


int main(void) {
    
    char str[] = "test";
    
    printf("Call by value\n");
    printf("-------------\n");
    printf("Before: %s\n", str);
    call_by_value(str);
    printf("After: %s\n\n", str);

    printf("Call by reference\n");
    printf("-----------------\n");
    printf("Before: %s\n", str);
    call_by_reference(str);
    printf("After: %s\n", str);
    
    return 0;
}