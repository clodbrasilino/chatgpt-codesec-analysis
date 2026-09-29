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

int get_n_smallest(const int *data, size_t data_len, size_t n,
                   int *out, size_t out_len)
{
    int *copy;
    size_t copy_size;
    size_t out_size;
    size_t i;

    if (data == NULL || out == NULL) {
        return -1;
    }
    if (n == 0 || n > data_len || n > out_len) {
        return -1;
    }
    if (data_len > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    if (n > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    if (out_len > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    copy_size = data_len * sizeof(int);
    out_size = n * sizeof(int);

    if (out_size > copy_size) {
        return -1;
    }
    if (out_size > out_len * sizeof(int)) {
        return -1;
    }

    copy = malloc(copy_size);
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
    int dataset[] = { 42, 7, 19, 3, 88, 15, 1, 64, 23, 9 };
    size_t dataset_len = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 4;
    int *result;
    size_t i;

    if (n > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Requested size too large\n");
        return EXIT_FAILURE;
    }

    result = malloc(n * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (get_n_smallest(dataset, dataset_len, n, result, n) != 0) {
        fprintf(stderr, "Failed to get n smallest items\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("The %zu smallest items:", n);
    for (i = 0; i < n; i++) {
        printf(" %d", result[i]);
    }
    printf("\n");

    free(result);

    return EXIT_SUCCESS;
}