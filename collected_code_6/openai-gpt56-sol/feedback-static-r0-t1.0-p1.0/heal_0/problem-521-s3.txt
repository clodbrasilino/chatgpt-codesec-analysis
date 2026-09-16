#include <stdio.h>
#include <stdlib.h>

static int is_scalene(double a, double b, double c)
{
    return a > 0.0 && b > 0.0 && c > 0.0 &&
           a + b > c && a + c > b && b + c > a &&
           a != b && a != c && b != c;
}

int main(void)
{
    double a;
    double b;
    double c;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_scalene(a, b, c)) {
        puts("The triangle is scalene.");
    } else {
        puts("The triangle is not scalene.");
    }

    return EXIT_SUCCESS;
}