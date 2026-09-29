#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void map_power(const int *bases, const int *indices, double *results, size_t length) {
    if (bases == NULL || indices == NULL || results == NULL) {
        return;
    }

    for (size_t i = 0; i < length; i++) {
        results[i] = pow((double)bases[i], (double)indices[i]);
    }
}

int main(void) {
    const int bases[] = {2, 3, 4, 5};
    const int indices[] = {1, 2, 3, 4};
    size_t length = sizeof(bases) / sizeof(bases[0]);

    double *results = (double *)malloc(length * sizeof(double));
    if (results == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    map_power(bases, indices, results, length);

    for (size_t i = 0; i < length; i++) {
        printf("%.0f ", results[i]);
    }
    printf("\n");

    free(results);
    return 0;
}