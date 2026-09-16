#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int extractMinMaxK(int *arr, size_t n, size_t k, int **minK, int **maxK) {
    if (arr == NULL || minK == NULL || maxK == NULL) {
        return -1;
    }
    if (k == 0 || k > n) {
        return -1;
    }

    int *temp = malloc(n * sizeof(int));
    if (temp == NULL) {
        return -1;
    }
    memcpy(temp, arr, n * sizeof(int));

    qsort(temp, n, sizeof(int), compare);

    *minK = malloc(k * sizeof(int));
    if (*minK == NULL) {
        free(temp);
        return -1;
    }

    *maxK = malloc(k * sizeof(int));
    if (*maxK == NULL) {
        free(*minK);
        *minK = NULL;
        free(temp);
        return -1;
    }

    memcpy(*minK, temp, k * sizeof(int));
    memcpy(*maxK, temp + (n - k), k * sizeof(int));

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