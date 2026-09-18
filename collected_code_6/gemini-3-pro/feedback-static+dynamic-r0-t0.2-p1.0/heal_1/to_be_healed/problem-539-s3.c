#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double* power_of_bases(const double* bases, const double* indices, size_t length) {
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
    double bases[] = {10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0};
    /* Possible weaknesses found:
     *  Variable 'indices' can be declared as const array [constVariable]
     */
    double indices[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    size_t length = sizeof(bases) / sizeof(bases[0]);

    double* results = power_of_bases(bases, indices, length);

    if (results != NULL) {
        for (size_t i = 0; i < length; ++i) {
            printf("%.2f ", results[i]);
        }
        printf("\n");
        free(results);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}