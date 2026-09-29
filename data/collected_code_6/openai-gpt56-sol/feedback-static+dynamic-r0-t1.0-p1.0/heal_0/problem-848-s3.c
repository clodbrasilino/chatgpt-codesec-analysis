#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int trapezium_area(double base1, double base2, double height, double *area)
{
    if (area == NULL ||
        !isfinite(base1) ||
        !isfinite(base2) ||
        !isfinite(height) ||
        base1 < 0.0 ||
        base2 < 0.0 ||
        height < 0.0) {
        return 0;
    }

    *area = ((base1 / 2.0) + (base2 / 2.0)) * height;
    return isfinite(*area);
}

int main(void)
{
    double base1 = 0.0;
    double base2 = 0.0;
    double height = 0.0;
    double area = 0.0;

    if (printf("Enter the two parallel sides and the height: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lf %lf %lf", &base1, &base2, &height) != 3) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!trapezium_area(base1, base2, height, &area)) {
        fprintf(stderr, "Values must be finite and nonnegative, and the result must be representable.\n");
        return EXIT_FAILURE;
    }

    if (printf("Area of the trapezium: %.6f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}