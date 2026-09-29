#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int extract_min_max_k(const int *tuple, size_t n, size_t k,
                      int *min_out, int *max_out)
{
    int *copy = NULL;
    size_t i;

    if (tuple == NULL || min_out == NULL || max_out == NULL) {
        return -1;
    }
    if (n == 0U || k == 0U || k > n) {
        return -1;
    }

    copy = malloc(n * sizeof(int));
    if (copy == NULL) {
        return -1;
    }

    memcpy(copy, tuple, n * sizeof(int));
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
    int tuple[] = {5, 20, 3, 7, 6, 8, 100, 1, 44, 9};
    size_t n = sizeof(tuple) / sizeof(tuple[0]);
    size_t k = 3U;
    int *min_k = NULL;
    int *max_k = NULL;
    size_t i;

    min_k = malloc(k * sizeof(int));
    if (min_k == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    max_k = malloc(k * sizeof(int));
    if (max_k == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(min_k);
        return EXIT_FAILURE;
    }

    if (extract_min_max_k(tuple, n, k, min_k, max_k) != 0) {
        fprintf(stderr, "Extraction failed\n");
        free(min_k);
        free(max_k);
        return EXIT_FAILURE;
    }

    printf("Minimum %zu elements: ", k);
    for (i = 0U; i < k; i++) {
        printf("%d ", min_k[i]);
    }
    printf("\n");

    printf("Maximum %zu elements: ", k);
    for (i = 0U; i < k; i++) {
        printf("%d ", max_k[i]);
    }
    printf("\n");

    free(min_k);
    free(max_k);
    return EXIT_SUCCESS;
}