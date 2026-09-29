#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*index_map_fn)(double value, size_t index);

static double power_by_index(double value, size_t index)
{
    return pow(value, (double)index);
}

static double *map_with_index(const double *input, size_t length, index_map_fn fn)
{
    double *result = NULL;
    size_t i;

    if (input == NULL || fn == NULL || length == 0U) {
        return NULL;
    }

    if (length > SIZE_MAX / sizeof(double)) {
        return NULL;
    }

    result = (double *)malloc(length * sizeof(double));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < length; i++) {
        result[i] = fn(input[i], i);
    }

    return result;
}

int main(void)
{
    double bases[] = { 10.0, 2.0, 3.0, 4.0, 5.0 };
    size_t length = sizeof(bases) / sizeof(bases[0]);
    double *powers = NULL;
    size_t i;

    powers = map_with_index(bases, length, power_by_index);
    if (powers == NULL) {
        (void)fprintf(stderr, "Failed to compute powers list\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < length; i++) {
        if (printf("%.0f\n", powers[i]) < 0) {
            free(powers);
            return EXIT_FAILURE;
        }
    }

    free(powers);
    powers = NULL;

    return EXIT_SUCCESS;
}