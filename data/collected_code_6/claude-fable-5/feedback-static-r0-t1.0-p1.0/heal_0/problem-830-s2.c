#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double round_up(double value, int digits, int *status);

double round_up(double value, int digits, int *status)
{
    double factor;
    double scaled;
    double result;

    *status = 0;

    if (!isfinite(value)) {
        *status = -1;
        return 0.0;
    }

    if (digits < 0 || digits > 15) {
        *status = -1;
        return 0.0;
    }

    factor = pow(10.0, (double)digits);
    if (!isfinite(factor) || factor <= 0.0) {
        *status = -1;
        return 0.0;
    }

    scaled = value * factor;
    if (!isfinite(scaled)) {
        *status = -1;
        return 0.0;
    }

    result = ceil(scaled) / factor;
    if (!isfinite(result)) {
        *status = -1;
        return 0.0;
    }

    return result;
}

int main(void)
{
    double number;
    int digits;
    int status;
    double result;

    printf("Enter a number: ");
    if (scanf("%lf", &number) != 1) {
        fprintf(stderr, "Invalid number input\n");
        return EXIT_FAILURE;
    }

    printf("Enter number of digits (0-15): ");
    if (scanf("%d", &digits) != 1) {
        fprintf(stderr, "Invalid digits input\n");
        return EXIT_FAILURE;
    }

    result = round_up(number, digits, &status);
    if (status != 0) {
        fprintf(stderr, "Rounding failed: invalid input or overflow\n");
        return EXIT_FAILURE;
    }

    printf("Rounded up value: %.*f\n", digits, result);

    return EXIT_SUCCESS;
}