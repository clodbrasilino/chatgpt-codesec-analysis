#include <stdio.h>
#include <stdlib.h>

int find_product(int *array, size_t size, long long *product) {
    if (array == NULL || product == NULL) {
        return -1;
    }

    *product = (size > 0) ? 1 : 0;

    size_t *counts = (size_t *)calloc(size, sizeof(size_t));
    if (counts == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (array[i] == array[j]) {
                counts[i]++;
            }
        }
    }

    for (size_t i = 0; i < size; i++) {
        if (counts[i] == 1) {
            *product *= array[i];
        }
    }

    free(counts);
    return 0;
}

int main(void) {
    int arr[] = {2, 3, 4, 5, 3, 6, 2};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    long long product;
    int result = find_product(arr, size, &product);

    if (result == 0) {
        printf("%lld\n", product);
    } else {
        fprintf(stderr, "Error calculating product\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}