#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *map_power(const int *bases, const int *indices, size_t length) {
    if (bases == NULL || indices == NULL || length == 0) {
        return NULL;
    }

    int *result = (int *)malloc(length * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; i++) {
        if (indices[i] < 0) {
            free(result);
            return NULL;
        }
        result[i] = (int)pow(bases[i], indices[i]);
    }

    return result;
}

int main(void) {
    int bases[] = {2, 3, 5, 7};
    /* Possible weaknesses found:
     *  Variable 'indices' can be declared as const array [constVariable]
     */
    int indices[] = {3, 2, 4, 1};
    size_t length = sizeof(bases) / sizeof(bases[0]);

    int *result = map_power(bases, indices, length);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);

    return EXIT_SUCCESS;
}