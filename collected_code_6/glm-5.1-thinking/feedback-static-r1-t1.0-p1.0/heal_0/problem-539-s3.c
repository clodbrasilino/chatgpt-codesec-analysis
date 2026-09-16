#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double power_op(double base, double index) {
    return pow(base, index);
}

double *map(const double *bases, const double *indices, size_t length, double (*operation)(double, double)) {
    if (bases == NULL || indices == NULL || operation == NULL || length == 0) {
        return NULL;
    }

    double *result = malloc(length * sizeof(double));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; i++) {
        result[i] = operation(bases[i], indices[i]);
    }

    return result;
}

int main(void) {
    double bases[] = {2.0, 3.0, 4.0, 5.0};
    double indices[] = {0.0, 1.0, 2.0, 3.0};
    size_t length = sizeof(bases) / sizeof(bases[0]);

    double *result = map(bases, indices, length, power_op);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; i++) {
        printf("%.2f ", result[i]);
    }
    printf("\n");

    free(result);

    return EXIT_SUCCESS;
}