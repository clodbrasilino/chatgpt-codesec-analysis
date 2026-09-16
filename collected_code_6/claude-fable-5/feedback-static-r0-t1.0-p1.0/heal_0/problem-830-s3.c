#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

double round_up(double value, int digits, int *error)
{
    double factor;
    double scaled;

    if (error == NULL) {
        return 0.0;
    }

    *error = 0;

    if (digits < 0 || digits > 15) {
        *error = 1;
        return 0.0;
    }

    if (isnan(value) || isinf(value)) {
        *error = 1;
        return 0.0;
    }

    factor = pow(10.0, (double)digits);

    errno = 0;
    scaled = value * factor;

    if (isinf(scaled) || errno == ERANGE) {
        *error = 1;
        return 0.0;
    }

    scaled = ceil(scaled);

    return scaled / factor;
}

int main(void)
{
    double number;
    int digits;
    int error;
    double result;

    printf("Enter a number: ");
    if (scanf("%lf", &number) != 1) {
        fprintf(stderr, "Invalid number input.\n");
        return EXIT_FAILURE;
    }

    printf("Enter number of digits (0-15): ");
    if (scanf("%d", &digits) != 1) {
        fprintf(stderr, "Invalid digits input.\n");
        return EXIT_FAILURE;
    }

    result = round_up(number, digits, &error);

    if (error != 0) {
        fprintf(stderr, "Rounding failed due to invalid input or overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Rounded up value: %.*f\n", digits, result);

    return EXIT_SUCCESS;
}