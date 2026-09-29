#include <stdio.h>
#include <stdlib.h>

static int is_scalene(double a, double b, double c)
{
    return a > 0.0 && b > 0.0 && c > 0.0 &&
           a < b + c && b < a + c && c < a + b &&
           a != b && b != c && a != c;
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

    if (a <= 0.0 || b <= 0.0 || c <= 0.0 ||
        a >= b + c || b >= a + c || c >= a + b) {
        fprintf(stderr, "The sides do not form a valid triangle\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", is_scalene(a, b, c) ? "Scalene" : "Not scalene");

    return EXIT_SUCCESS;
}