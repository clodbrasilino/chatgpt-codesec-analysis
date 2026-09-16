#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_discriminant(double a, double b, double c, double *result)
{
    if (result == NULL || !isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return 0;
    }

    errno = 0;
    const double discriminant = fma(b, b, -4.0 * a * c);

    if (errno != 0 || !isfinite(discriminant)) {
        return 0;
    }

    *result = discriminant;
    return 1;
}

int main(void)
{
    double a;
    double b;
    double c;
    double discriminant;

    if (printf("Enter coefficients a, b, and c: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!calculate_discriminant(a, b, c, &discriminant)) {
        fprintf(stderr, "Unable to calculate the discriminant.\n");
        return EXIT_FAILURE;
    }

    if (printf("Discriminant: %.17g\n", discriminant) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}