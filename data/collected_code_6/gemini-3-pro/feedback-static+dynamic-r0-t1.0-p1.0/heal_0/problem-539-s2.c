#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double* map_power(const double* bases, const double* indices, size_t length) {
    if (bases == NULL || indices == NULL || length == 0) {
        return NULL;
    }

    double* results = (double*)malloc(length * sizeof(double));
    if (results == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        results[i] = pow(bases[i], indices[i]);
    }

    return results;
}

int main(void) {
    double bases[] = {2.0, 3.0, 4.0, 5.0};
    double indices[] = {1.0, 2.0, 3.0, 4.0};
    size_t length = sizeof(bases) / sizeof(bases[0]);

    double* results = map_power(bases, indices, length);

    if (results != NULL) {
        for (size_t i = 0; i < length; ++i) {
            printf("%f ^ %f = %f\n", bases[i], indices[i], results[i]);
        }
        free(results);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return 1;
    }

    return 0;
}