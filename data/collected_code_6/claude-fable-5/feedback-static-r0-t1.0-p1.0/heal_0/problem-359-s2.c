#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int is_one_root_twice_other(double a, double b, double c)
{
    double lhs;
    double rhs;
    double epsilon = 1e-9;

    if (fabs(a) < epsilon) {
        return -1;
    }

    lhs = 2.0 * b * b;
    rhs = 9.0 * a * c;

    if (fabs(lhs - rhs) < epsilon * fmax(1.0, fmax(fabs(lhs), fabs(rhs)))) {
        return 1;
    }
    return 0;
}

int main(void)
{
    double a;
    double b;
    double c;
    int result;

    printf("Enter coefficient a: ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Invalid input for a\n");
        return EXIT_FAILURE;
    }

    printf("Enter coefficient b: ");
    if (scanf("%lf", &b) != 1) {
        fprintf(stderr, "Invalid input for b\n");
        return EXIT_FAILURE;
    }

    printf("Enter coefficient c: ");
    if (scanf("%lf", &c) != 1) {
        fprintf(stderr, "Invalid input for c\n");
        return EXIT_FAILURE;
    }

    result = is_one_root_twice_other(a, b, c);

    if (result == -1) {
        fprintf(stderr, "Not a quadratic equation: coefficient a is zero\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("Yes, one root is twice the other.\n");
    } else {
        printf("No, one root is not twice the other.\n");
    }

    return EXIT_SUCCESS;
}