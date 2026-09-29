#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int find_third_side(double side1, double side2, int hypotenuse_unknown,
                           double *result)
{
    if (result == NULL || !isfinite(side1) || !isfinite(side2) ||
        side1 <= 0.0 || side2 <= 0.0) {
        return -1;
    }

    errno = 0;

    if (hypotenuse_unknown) {
        *result = hypot(side1, side2);
    } else {
        const double hypotenuse = side1;
        const double known_leg = side2;

        if (hypotenuse <= known_leg) {
            return -1;
        }

        *result = sqrt((hypotenuse - known_leg) *
                       (hypotenuse + known_leg));
    }

    if (errno != 0 || !isfinite(*result)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    double side1 = 0.0;
    double side2 = 0.0;
    double result = 0.0;
    int hypotenuse_unknown = 0;

    printf("Enter two known sides: ");
    if (scanf("%lf %lf", &side1, &side2) != 2) {
        fprintf(stderr, "Invalid numeric input.\n");
        return EXIT_FAILURE;
    }

    printf("Enter 1 if the hypotenuse is unknown, or 0 if side1 is the hypotenuse: ");
    if (scanf("%d", &hypotenuse_unknown) != 1 ||
        (hypotenuse_unknown != 0 && hypotenuse_unknown != 1)) {
        fprintf(stderr, "Invalid selection.\n");
        return EXIT_FAILURE;
    }

    if (find_third_side(side1, side2, hypotenuse_unknown, &result) != 0) {
        fprintf(stderr, "The supplied sides do not form a valid right triangle.\n");
        return EXIT_FAILURE;
    }

    printf("Third side: %.10g\n", result);
    return EXIT_SUCCESS;
}