#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int calculate_average(const double *numbers, size_t length, double *average)
{
    size_t i;
    double sum = 0.0;

    if (numbers == NULL || average == NULL || length == 0U) {
        return 0;
    }

    for (i = 0U; i < length; ++i) {
        sum += numbers[i];
    }

    *average = sum / (double)length;
    return 1;
}

int main(void)
{
    double *numbers = NULL;
    double average;
    size_t length;
    size_t i;
    int status = EXIT_FAILURE;

    if (printf("Enter the number of values: ") < 0) {
        goto cleanup;
    }

    if (scanf("%zu", &length) != 1 || length == 0U ||
        length > SIZE_MAX / sizeof(*numbers)) {
        fprintf(stderr, "Invalid list length.\n");
        goto cleanup;
    }

    numbers = malloc(length * sizeof(*numbers));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        goto cleanup;
    }

    if (printf("Enter %zu numbers: ", length) < 0) {
        goto cleanup;
    }

    for (i = 0U; i < length; ++i) {
        if (scanf("%lf", &numbers[i]) != 1) {
            fprintf(stderr, "Invalid number.\n");
            goto cleanup;
        }
    }

    if (!calculate_average(numbers, length, &average)) {
        fprintf(stderr, "Unable to calculate the average.\n");
        goto cleanup;
    }

    if (printf("Average: %.10g\n", average) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(numbers);
    return status;
}