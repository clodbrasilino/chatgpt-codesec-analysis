#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*map_function_t)(double, size_t);

double power_of_index(double base, size_t index) {
    return pow(base, (double)index);
}

double* map(const double *array, size_t size, map_function_t func) {
    if (array == NULL || func == NULL || size == 0) {
        return NULL;
    }

    double *result = (double *)malloc(size * sizeof(double));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; ++i) {
        result[i] = func(array[i], i);
    }

    return result;
}

int main(void) {
    const double bases[] = {10.0, 2.0, 3.0, 4.0, 5.0};
    size_t size = sizeof(bases) / sizeof(bases[0]);

    double *powered_values = map(bases, size, power_of_index);
    if (powered_values == NULL) {
        fprintf(stderr, "Error: Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; ++i) {
        printf("%f\n", powered_values[i]);
    }

    free(powered_values);
    powered_values = NULL;

    return EXIT_SUCCESS;
}