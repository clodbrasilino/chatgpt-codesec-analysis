#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int is_one_root_twice_other(double a, double b, double c)
{
    double lhs;
    double rhs;
    double discriminant;

    if (fabs(a) < 1e-12) {
        return -1;
    }

    discriminant = (b * b) - (4.0 * a * c);
    if (discriminant < 0.0) {
        return -1;
    }

    lhs = 2.0 * b * b;
    rhs = 9.0 * a * c;

    if (fabs(lhs - rhs) < 1e-9) {
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

    printf("Enter coefficients a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = is_one_root_twice_other(a, b, c);

    if (result == -1) {
        printf("Invalid equation or no real roots\n");
    } else if (result == 1) {
        printf("Yes, one root is twice the other\n");
    } else {
        printf("No, one root is not twice the other\n");
    }

    return EXIT_SUCCESS;
}