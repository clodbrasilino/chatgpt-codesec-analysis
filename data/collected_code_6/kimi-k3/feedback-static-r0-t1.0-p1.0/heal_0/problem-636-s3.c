#include <stdio.h>
#include <math.h>

int check_reciprocal_roots(double a, double b, double c)
{
    double discriminant;
    double product;

    if (a == 0.0 || c == 0.0) {
        return 0;
    }

    discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0) {
        return 0;
    }

    product = c / a;

    if (fabs(product - 1.0) < 1e-9) {
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

    printf("Enter coefficients a, b, and c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    result = check_reciprocal_roots(a, b, c);

    if (result) {
        printf("The roots are reciprocal of each other.\n");
    } else {
        printf("The roots are not reciprocal of each other.\n");
    }

    return 0;
}