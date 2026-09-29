#include <stdio.h>
#include <stdlib.h>

int find_max_freq(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    int *counts = calloc(n, sizeof(int));
    if (counts == NULL) {
        exit(EXIT_FAILURE);
    }

    int max_count = 0;
    int max_item = arr[0];

    for (size_t i = 0; i < n; i++) {
        if (counts[i] == -1) {
            continue;
        }

        counts[i] = 1;
        for (size_t j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                counts[i]++;
                counts[j] = -1;
            }
        }

        if (counts[i] > max_count) {
            max_count = counts[i];
            max_item = arr[i];
        }
    }

    free(counts);
    return max_item;
}

int main(void) {
    int arr1[] = {1, 2, 3, 2, 4, 2, 5};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", find_max_freq(arr1, n1));

    int arr2[] = {1, 2, 3, 4, 5};
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", find_max_freq(arr2, n2));

    return EXIT_SUCCESS;
}