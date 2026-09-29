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

int get_n_smallest(const int *data, size_t data_len, size_t n, int *result)
{
    int *copy;

    if (data == NULL || result == NULL) {
        return -1;
    }
    if (n == 0 || n > data_len) {
        return -1;
    }
    if (data_len > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    copy = malloc(data_len * sizeof(int));
    if (copy == NULL) {
        return -1;
    }

    memcpy(copy, data, data_len * sizeof(int));
    qsort(copy, data_len, sizeof(int), compare_ints);
    memcpy(result, copy, n * sizeof(int));

    free(copy);
    return 0;
}

int main(void)
{
    int dataset[] = { 42, 7, 19, 3, 88, 15, 1, 56, 23, 9 };
    size_t dataset_len = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 4;
    int *smallest;
    size_t i;

    smallest = malloc(n * sizeof(int));
    if (smallest == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (get_n_smallest(dataset, dataset_len, n, smallest) != 0) {
        fprintf(stderr, "Failed to get n smallest items\n");
        free(smallest);
        return EXIT_FAILURE;
    }

    printf("The %zu smallest items are:", n);
    for (i = 0; i < n; i++) {
        printf(" %d", smallest[i]);
    }
    printf("\n");

    free(smallest);
    return EXIT_SUCCESS;
}