#include <stdio.h>
#include <stdlib.h>

int findFirstElementOccurringKTimes(const int *arr, size_t size, size_t k) {
    if (arr == NULL || k == 0 || size == 0) {
        return -1;
    }

    size_t *counts = (size_t *)calloc(size, sizeof(size_t));
    if (counts == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (arr[i] == arr[j]) {
                counts[i]++;
            }
        }
    }

    int result = -1;
    for (size_t i = 0; i < size; i++) {
        if (counts[i] == k) {
            result = arr[i];
            break;
        }
    }

    free(counts);
    return result;
}

int main(void) {
    int arr[] = {1, 7, 4, 3, 4, 8, 7};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t k = 2;

    int result = findFirstElementOccurringKTimes(arr, size, k);

    if (result != -1) {
        printf("First element occurring %zu times: %d\n", k, result);
    } else {
        printf("No element found occurring %zu times.\n", k);
    }

    return 0;
}