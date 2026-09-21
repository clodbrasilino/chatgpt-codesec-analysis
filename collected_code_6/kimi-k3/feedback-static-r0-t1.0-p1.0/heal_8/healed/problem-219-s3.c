#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int compare(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int extractMinMaxK(const int *arr, size_t n, size_t k, int **minK, int **maxK) {
    if (arr == NULL || minK == NULL || maxK == NULL) {
        return -1;
    }
    if (k == 0 || k > n) {
        return -1;
    }
    if (n > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    if (k > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    size_t temp_size = n * sizeof(int);
    size_t k_size = k * sizeof(int);

    int *temp = malloc(temp_size);
    if (temp == NULL) {
        return -1;
    }

    if (temp_size > 0) {
        memcpy(temp, arr, temp_size);
    }

    qsort(temp, n, sizeof(int), compare);

    *minK = malloc(k_size);
    if (*minK == NULL) {
        free(temp);
        return -1;
    }

    *maxK = malloc(k_size);
    if (*maxK == NULL) {
        free(*minK);
        *minK = NULL;
        free(temp);
        return -1;
    }

    if (k_size > 0 && k_size <= temp_size && (n - k) * sizeof(int) + k_size <= temp_size) {
        memcpy(*minK, temp, k_size);
        memcpy(*maxK, temp + (n - k), k_size);
    }

    free(temp);
    return 0;
}

int main(void) {
    int arr[] = {5, 2, 9, 1, 7, 3, 8, 4, 6};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t k = 3;
    int *minK = NULL;
    int *maxK = NULL;

    if (extractMinMaxK(arr, n, k, &minK, &maxK) != 0) {
        fprintf(stderr, "Error: Invalid input or memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Minimum %zu elements: ", k);
    for (size_t i = 0; i < k; i++) {
        printf("%d ", minK[i]);
    }
    printf("\n");

    printf("Maximum %zu elements: ", k);
    for (size_t i = 0; i < k; i++) {
        printf("%d ", maxK[i]);
    }
    printf("\n");

    free(minK);
    free(maxK);

    return EXIT_SUCCESS;
}