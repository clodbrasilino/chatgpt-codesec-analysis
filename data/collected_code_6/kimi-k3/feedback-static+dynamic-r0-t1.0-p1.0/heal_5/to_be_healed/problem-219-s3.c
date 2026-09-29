#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int compare(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) return -1;
    if (x > y) return 1;
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

    int *temp = malloc(n * sizeof(int));
    if (temp == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  did you mean 'memcpy'?
     *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (memcpy_s(temp, n * sizeof(int), arr, n * sizeof(int)) != 0) {
        free(temp);
        return -1;
    }

    qsort(temp, n, sizeof(int), compare);

    if (k > SIZE_MAX / sizeof(int)) {
        free(temp);
        return -1;
    }

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

    if (memcpy_s(*minK, k * sizeof(int), temp, k * sizeof(int)) != 0) {
        free(*minK);
        *minK = NULL;
        free(*maxK);
        *maxK = NULL;
        free(temp);
        return -1;
    }

    if (memcpy_s(*maxK, k * sizeof(int), temp + (n - k), k * sizeof(int)) != 0) {
        free(*minK);
        *minK = NULL;
        free(*maxK);
        *maxK = NULL;
        free(temp);
        return -1;
    }

    free(temp);
    return 0;
}

/* Possible weaknesses found:
 *  'memcpy' declared here
 */
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