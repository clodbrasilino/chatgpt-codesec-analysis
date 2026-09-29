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

    if (printf("Enter three side lengths: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (a <= 0.0 || b <= 0.0 || c <= 0.0 ||
        a + b <= c || a + c <= b || b + c <= a) {
        fprintf(stderr, "The side lengths do not form a valid triangle.\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", is_scalene(a, b, c)
                         ? "The triangle is scalene."
                         : "The triangle is not scalene.") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}