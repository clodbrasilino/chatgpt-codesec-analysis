#include <stdio.h>
#include <stdlib.h>

int divide_first_even_by_first_odd(const int values[], size_t count, double *result)
{
    if (values == NULL || result == NULL) {
        return -1;
    }

    int even = 0;
    int odd = 0;
    int found_even = 0;
    int found_odd = 0;

    for (size_t i = 0; i < count && (!found_even || !found_odd); ++i) {
        if (!found_even && values[i] % 2 == 0) {
            even = values[i];
            found_even = 1;
        }

        if (!found_odd && values[i] % 2 != 0) {
            odd = values[i];
            found_odd = 1;
        }
    }

    if (!found_even || !found_odd) {
        return -1;
    }

    *result = (double)even / (double)odd;
    return 0;
}

int main(void)
{
    size_t count = 0;

    if (printf("Enter the number of elements: ") < 0 ||
        scanf("%zu", &count) != 1 ||
        count == 0 ||
        count > SIZE_MAX / sizeof(int)) {
        fputs("Invalid element count.\n", stderr);
        return EXIT_FAILURE;
    }

    int *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Enter %zu integers: ", count) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fputs("Invalid input.\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    double result = 0.0;
    if (divide_first_even_by_first_odd(values, count, &result) != 0) {
        fputs("The list must contain both an even and an odd number.\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    free(values);

    if (printf("Division result: %.6f\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}