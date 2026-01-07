#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Working.");
    fflush(stdout);
    sleep(1);
    printf("\b-");
    fflush(stdout);
    sleep(1);
    printf("\b\\");
    fflush(stdout);
    sleep(1);
    printf("\b|");
return 0;
}