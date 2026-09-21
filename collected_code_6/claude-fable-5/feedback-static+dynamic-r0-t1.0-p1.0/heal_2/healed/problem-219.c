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

int extract_min_max_k(const int *arr, size_t n, size_t k,
                      int *min_out, int *max_out)
{
    int *copy;
    size_t i;
    size_t copy_size;

    if (arr == NULL || min_out == NULL || max_out == NULL) {
        return -1;
    }
    if (n == 0U || k == 0U || k > n) {
        return -1;
    }
    if (n > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    copy_size = n * sizeof(int);

    copy = malloc(copy_size);
    if (copy == NULL) {
        return -1;
    }

    for (i = 0U; i < n; i++) {
        copy[i] = arr[i];
    }

    qsort(copy, n, sizeof(int), compare_ints);

    for (i = 0U; i < k; i++) {
        min_out[i] = copy[i];
        max_out[i] = copy[n - k + i];
    }

    free(copy);
    return 0;
}

int main(void)
{
    int data[] = { 5, 20, 3, 7, 6, 8, 100, -2, 45, 9 };
    size_t n = sizeof(data) / sizeof(data[0]);
    size_t k = 3U;
    int *min_vals;
    int *max_vals;
    size_t i;
    int status;

    if (k > n) {
        fprintf(stderr, "Invalid k value\n");
        return EXIT_FAILURE;
    }

    min_vals = malloc(k * sizeof(int));
    if (min_vals == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    max_vals = malloc(k * sizeof(int));
    if (max_vals == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(min_vals);
        return EXIT_FAILURE;
    }

    status = extract_min_max_k(data, n, k, min_vals, max_vals);
    if (status != 0) {
        fprintf(stderr, "Extraction failed\n");
        free(min_vals);
        free(max_vals);
        return EXIT_FAILURE;
    }

    printf("Minimum %zu elements: ", k);
    for (i = 0U; i < k; i++) {
        printf("%d ", min_vals[i]);
    }
    printf("\n");

    printf("Maximum %zu elements: ", k);
    for (i = 0U; i < k; i++) {
        printf("%d ", max_vals[i]);
    }
    printf("\n");

    free(min_vals);
    free(max_vals);
    return EXIT_SUCCESS;
}