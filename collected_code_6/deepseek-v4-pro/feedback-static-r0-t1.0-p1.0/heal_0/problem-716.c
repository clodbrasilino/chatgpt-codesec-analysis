#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <float.h>

double perimeter_of_rhombus(double side) {
    if (side <= 0.0 || !isfinite(side)) {
        errno = EINVAL;
        return -1.0;
    }
    if (side > DBL_MAX / 4.0) {
        errno = ERANGE;
        return -1.0;
    }
    return 4.0 * side;
}

int main(void) {
    double side;
    printf("Enter the side length of the rhombus: ");
    if (scanf("%lf", &side) != 1) {
        fprintf(stderr, "Error: Invalid input. Please enter a numeric value.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    double perimeter = perimeter_of_rhombus(side);
    if (perimeter < 0.0 || errno != 0) {
        if (errno == EINVAL) {
            fprintf(stderr, "Error: Side length must be a positive finite number.\n");
        } else if (errno == ERANGE) {
            fprintf(stderr, "Error: Resulting perimeter exceeds representable range.\n");
        } else {
            fprintf(stderr, "Error: Failed to compute perimeter.\n");
        }
        return EXIT_FAILURE;
    }

    printf("Perimeter of the rhombus: %.10g\n", perimeter);
    return EXIT_SUCCESS;
}