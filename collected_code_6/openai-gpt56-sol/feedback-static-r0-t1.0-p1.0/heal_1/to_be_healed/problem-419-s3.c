#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

static int round_and_calculate(const double *numbers, size_t length, double *result)
{
    double sum = 0.0;

    if (numbers == NULL || result == NULL || length == 0U) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        double rounded;

        if (!isfinite(numbers[i])) {
            return -1;
        }

        rounded = round(numbers[i]);

        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'DBL_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'DBL_MAX'
         */
        if ((sum > 0.0 && rounded > DBL_MAX - sum) ||
            /* Possible weaknesses found:
             *  use of undeclared identifier 'DBL_MAX'
             */
            (sum < 0.0 && rounded < -DBL_MAX - sum)) {
            return -1;
        }

        sum += rounded;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'DBL_MAX'
     */
    if (sum != 0.0 && (double)length > DBL_MAX / fabs(sum)) {
        return -1;
    }

    *result = sum * (double)length;
    return isfinite(*result) ? 0 : -1;
}

int main(void)
{
    double *numbers = NULL;
    double result;
    size_t length;

    if (printf("Enter the number of values: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &length) != 1 || length == 0U ||
        length > SIZE_MAX / sizeof(*numbers)) {
        fprintf(stderr, "Invalid list length.\n");
        return EXIT_FAILURE;
    }

    numbers = malloc(length * sizeof(*numbers));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter %zu numbers: ", length) < 0) {
        free(numbers);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%lf", &numbers[i]) != 1 || !isfinite(numbers[i])) {
            fprintf(stderr, "Invalid number.\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    if (round_and_calculate(numbers, length, &result) != 0) {
        fprintf(stderr, "Calculation failed.\n");
        free(numbers);
        return EXIT_FAILURE;
    }

    free(numbers);

    if (printf("%.0f\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}