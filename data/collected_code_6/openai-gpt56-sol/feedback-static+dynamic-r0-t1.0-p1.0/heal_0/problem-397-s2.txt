#include <stdio.h>
#include <stdlib.h>

static double median_of_three(double a, double b, double c)
{
    if ((a <= b && b <= c) || (c <= b && b <= a)) {
        return b;
    }

    if ((b <= a && a <= c) || (c <= a && a <= b)) {
        return a;
    }

    return c;
}

int main(void)
{
    double first;
    double second;
    double third;

    if (scanf("%lf %lf %lf", &first, &second, &third) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.17g\n", median_of_three(first, second, third));

    return EXIT_SUCCESS;
}