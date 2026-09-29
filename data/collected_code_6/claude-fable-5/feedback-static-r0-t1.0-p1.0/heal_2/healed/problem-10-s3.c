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

int get_n_smallest(const int *data, size_t data_len, size_t n, int *out)
{
    int *copy = NULL;
    size_t i;

    if (data == NULL || out == NULL) {
        return -1;
    }
    if (n == 0 || n > data_len) {
        return -1;
    }
    if (data_len > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    copy = calloc(data_len, sizeof(int));
    if (copy == NULL) {
        return -1;
    }

    for (i = 0; i < data_len; i++) {
        copy[i] = data[i];
    }

    qsort(copy, data_len, sizeof(int), compare_ints);

    for (i = 0; i < n; i++) {
        out[i] = copy[i];
    }

    free(copy);
    return 0;
}

int main(void)
{
    int dataset[] = { 42, 7, 19, 3, 88, 15, 1, 64, 23, 5 };
    size_t dataset_len = sizeof(dataset) / sizeof(dataset[0]);
    const size_t n = 4;
    int *result = NULL;
    size_t i;

    result = calloc(n, sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (get_n_smallest(dataset, dataset_len, n, result) != 0) {
        fprintf(stderr, "Failed to get n smallest items\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("The %zu smallest items are:", n);
    for (i = 0; i < n; i++) {
        printf(" %d", result[i]);
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}