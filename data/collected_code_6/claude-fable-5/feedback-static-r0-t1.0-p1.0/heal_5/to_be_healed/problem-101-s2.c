#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

static int find_kth_element(const int *arr, size_t n, size_t k, int *result)
{
    int *copy;
    size_t total_size;

    if (arr == NULL || result == NULL || n == 0 || k == 0 || k > n) {
        return -1;
    }

    if (n > SIZE_MAX / sizeof(*copy)) {
        return -1;
    }

    total_size = n * sizeof(*copy);

    copy = malloc(total_size);
    if (copy == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, arr, total_size);
    qsort(copy, n, sizeof(*copy), compare_ints);

    *result = copy[k - 1];
    free(copy);

    return 0;
}

int main(void)
{
    int arr[] = { 12, 3, 5, 7, 4, 19, 26 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t k = 3;
    int result = 0;

    if (find_kth_element(arr, n, k, &result) != 0) {
        fprintf(stderr, "Error: invalid input or allocation failure\n");
        return EXIT_FAILURE;
    }

    if (printf("The %zu-th smallest element is %d\n", k, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}