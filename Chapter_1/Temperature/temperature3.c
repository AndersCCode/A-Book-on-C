# include <stdio.h>

int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = -50.0;      // lower limit of temperature table
    upper = 50.0;    // uppler limit
    step = 5;      // step size

    celsius = lower;
    printf("Temp.\tTemp.\n");
    printf(" (C)\t (F)\n");
    printf("--------------\n");
    while (celsius <= upper) {
        fahr = ((celsius * (9.0/5.0)) + 32.0);
        printf("%2.0f\t%3.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
    return 0;
}
