#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*map_func)(double, size_t);

static double power_by_index(double base, size_t index)
{
    return pow(base, (double)index);
}

static double *map_apply(const double *input, size_t length, map_func func)
{
    double *result = NULL;
    size_t i;

    if (input == NULL || func == NULL || length == 0U) {
        return NULL;
    }

    if (length > SIZE_MAX / sizeof(double)) {
        return NULL;
    }

    result = malloc(length * sizeof(double));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < length; i++) {
        result[i] = func(input[i], i);
    }

    return result;
}

int main(void)
{
    double bases[] = { 10.0, 20.0, 30.0 };
    size_t length = sizeof(bases) / sizeof(bases[0]);
    double *powers = NULL;
    size_t i;

    powers = map_apply(bases, length, power_by_index);
    if (powers == NULL) {
        (void)fprintf(stderr, "Failed to compute powers\n");
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