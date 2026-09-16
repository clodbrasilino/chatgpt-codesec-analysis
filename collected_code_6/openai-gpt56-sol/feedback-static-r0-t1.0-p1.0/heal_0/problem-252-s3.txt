#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double magnitude;
    double angle;
} Polar;

static int complex_to_polar(double real, double imaginary, Polar *result)
{
    if (result == NULL || !isfinite(real) || !isfinite(imaginary)) {
        return -1;
    }

    errno = 0;
    result->magnitude = hypot(real, imaginary);
    result->angle = atan2(imaginary, real);

    if (errno != 0 || !isfinite(result->magnitude) || !isfinite(result->angle)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    double real = 0.0;
    double imaginary = 0.0;
    Polar result = {0.0, 0.0};

    if (printf("Enter the real and imaginary parts: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lf %lf", &real, &imaginary) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (complex_to_polar(real, imaginary, &result) != 0) {
        fprintf(stderr, "Unable to convert the complex number.\n");
        return EXIT_FAILURE;
    }

    if (printf("Magnitude: %.17g\nAngle (radians): %.17g\n",
               result.magnitude, result.angle) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}