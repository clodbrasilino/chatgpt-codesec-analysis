#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double power_mapper(double index, void *context) {
    if (context == NULL) {
        return 0.0;
    }
    double base = *(double *)context;
    return pow(base, index);
}

int map(const double *input, double *output, size_t length, double (*func)(double, void*), void *context) {
    if (input == NULL || output == NULL || func == NULL || context == NULL) {
        return -1;
    }
    for (size_t i = 0; i < length; i++) {
        output[i] = func(input[i], context);
    }
    return 0;
}

int main(void) {
    size_t length = 10;
    double base = 2.0;

    double *indices = malloc(length * sizeof(double));
    if (indices == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; i++) {
        indices[i] = (double)i;
    }

    double *powers = malloc(length * sizeof(double));
    if (powers == NULL) {
        free(indices);
        return EXIT_FAILURE;
    }

    if (map(indices, powers, length, power_mapper, &base) != 0) {
        free(powers);
        free(indices);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; i++) {
        printf("%.2f\n", powers[i]);
    }

    free(powers);
    free(indices);

    return EXIT_SUCCESS;
}