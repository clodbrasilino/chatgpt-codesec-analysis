#include <stdio.h>
#include <stdlib.h>

int find_first_k_occurrence(int *array, size_t size, int k) {
    if (array == NULL || k <= 0) {
        return -1;
    }

    int min_val = array[0];
    int max_val = array[0];
    for (size_t i = 1; i < size; i++) {
        if (array[i] < min_val) {
            min_val = array[i];
        }
        if (array[i] > max_val) {
            max_val = array[i];
        }
    }

    size_t range = 0;
    if (max_val >= min_val) {
        range = (size_t)(max_val - min_val) + 1;
    } else {
        range = (size_t)(min_val - max_val) + 1;
    }

    size_t *counts = (size_t *)calloc(range, sizeof(size_t));
    if (counts == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        counts[array[i] - min_val]++;
    }

    int result = -1;
    for (size_t i = 0; i < size; i++) {
        if (counts[array[i] - min_val] == k) {
            result = array[i];
            break;
        }
    }

    free(counts);
    return result;
}

int main(void) {
    int arr1[] = {1, 2, 3, 2, 1, 3, 4, 5, 4, 2, 2};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int k1 = 2;
    int res1 = find_first_k_occurrence(arr1, size1, k1);
    printf("%d\n", res1);

    int arr2[] = {5, 5, 5, 6, 6, 6};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 3;
    int res2 = find_first_k_occurrence(arr2, size2, k2);
    printf("%d\n", res2);

    int arr3[] = {10, 20, 30};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    int k3 = 1;
    int res3 = find_first_k_occurrence(arr3, size3, k3);
    printf("%d\n", res3);

    return 0;
}