#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int find_third_side(double side1, double side2, int hypotenuse_missing,
                           double *result)
{
    if (result == NULL || !isfinite(side1) || !isfinite(side2) ||
        side1 <= 0.0 || side2 <= 0.0) {
        return 0;
    }

    errno = 0;

    if (hypotenuse_missing) {
        *result = hypot(side1, side2);
    } else {
        double hypotenuse = side1;
        double leg = side2;

        if (hypotenuse <= leg) {
            return 0;
        }

        *result = sqrt((hypotenuse - leg) * (hypotenuse + leg));
    }

    return errno == 0 && isfinite(*result) && *result > 0.0;
}

int main(void)
{
    double side1 = 0.0;
    double side2 = 0.0;
    double result = 0.0;
    int hypotenuse_missing = 0;

    printf("Enter 1 if the hypotenuse is missing, or 0 if a leg is missing: ");
    if (scanf("%d", &hypotenuse_missing) != 1 ||
        (hypotenuse_missing != 0 && hypotenuse_missing != 1)) {
        fprintf(stderr, "Invalid selection.\n");
        return EXIT_FAILURE;
    }

    if (hypotenuse_missing) {
        printf("Enter the two legs: ");
    } else {
        printf("Enter the hypotenuse and known leg: ");
    }

    if (scanf("%lf %lf", &side1, &side2) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!find_third_side(side1, side2, hypotenuse_missing, &result)) {
        fprintf(stderr, "The supplied sides do not form a valid right triangle.\n");
        return EXIT_FAILURE;
    }

    printf("Third side: %.10g\n", result);
    return EXIT_SUCCESS;
}