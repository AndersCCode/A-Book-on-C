# include <stdio.h>

# define LOWER 0
# define UPPER 300
# define STEP 20

int main()
{
    int fahr;

    printf("Temp.\tTemp.\n");
    printf(" (F)\t (C)\n");
    printf("--------------\n");
    for (fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP)
        printf("%3d\t%6.1lf\n", fahr, ((5.0/9.0) * (fahr-32.0)));
    return 0;
}
