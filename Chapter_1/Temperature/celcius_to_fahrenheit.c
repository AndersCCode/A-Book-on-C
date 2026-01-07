# include <stdio.h>

int main()
{
    int celcius;
    
    printf("Temp.\tTemp.\n");
    printf(" (C)\t (F)\n");
    printf("--------------\n");
    for (celcius = -50; celcius <=50; celcius = celcius + 10)
        printf("%3d\t%6.1lf\n", celcius, (((9.0/5.0) * celcius) + 32.0));
    return 0;
}