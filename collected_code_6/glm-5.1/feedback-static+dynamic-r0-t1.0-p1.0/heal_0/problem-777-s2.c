#include <stdio.h>
#include <stdlib.h>

int sum_non_repeated(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    int *counts = (int *)calloc(size, sizeof(int));
    if (counts == NULL) {
        return 0;
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (array[i] == array[j]) {
                counts[i]++;
            }
        }
    }

    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        if (counts[i] == 1) {
            sum += array[i];
        }
    }

    free(counts);
    counts = NULL;

    return sum;
}

int main(void) {
    int arr[] = {1, 2, 3, 2, 4, 5, 1, 6};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int result = sum_non_repeated(arr, size);
    printf("%d\n", result);

    return 0;
}