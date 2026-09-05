#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

double multiply_and_divide(const double *numbers, size_t length, int *error)
{
    if (numbers == NULL || length == 0) {
        if (error != NULL) {
            *error = EINVAL;
        }
        return 0.0;
    }

    double result = 1.0;
    for (size_t i = 0; i < length; i++) {
        result *= numbers[i];
        if (isinf(result) || isnan(result)) {
            if (error != NULL) {
                *error = ERANGE;
            }
            return 0.0;
        }
    }

    result /= (double)length;

    if (error != NULL) {
        *error = 0;
    }
    return result;
}

int main(void)
{
    double numbers[] = {2.0, 3.0, 4.0, 5.0};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    int error = 0;

    double result = multiply_and_divide(numbers, length, &error);

    if (error != 0) {
        fprintf(stderr, "Error occurred during calculation\n");
        return EXIT_FAILURE;
    }

    printf("Result: %.2f\n", result);

    return EXIT_SUCCESS;
}