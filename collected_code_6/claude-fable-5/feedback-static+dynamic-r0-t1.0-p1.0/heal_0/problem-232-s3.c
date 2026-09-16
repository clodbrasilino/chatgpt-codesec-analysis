#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_desc(const void *a, const void *b)
{
    int lhs = *(const int *)a;
    int rhs = *(const int *)b;

    if (lhs < rhs) {
        return 1;
    }
    if (lhs > rhs) {
        return -1;
    }
    return 0;
}

int get_n_largest(const int *data, size_t size, size_t n, int *result)
{
    int *copy;

    if (data == NULL || result == NULL) {
        return -1;
    }
    if (size == 0U || n == 0U || n > size) {
        return -1;
    }
    if (size > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    copy = malloc(size * sizeof(int));
    if (copy == NULL) {
        return -1;
    }

    memcpy(copy, data, size * sizeof(int));
    qsort(copy, size, sizeof(int), compare_desc);
    memcpy(result, copy, n * sizeof(int));
    free(copy);

    return 0;
}

int main(void)
{
    int dataset[] = { 42, 7, 93, 15, 88, 3, 61, 27, 54, 99 };
    size_t size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 3U;
    int *largest;
    size_t i;

    largest = malloc(n * sizeof(int));
    if (largest == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (get_n_largest(dataset, size, n, largest) != 0) {
        fprintf(stderr, "Failed to get largest items\n");
        free(largest);
        return EXIT_FAILURE;
    }

    printf("The %zu largest items are:\n", n);
    for (i = 0U; i < n; i++) {
        printf("%d\n", largest[i]);
    }

    free(largest);
    return EXIT_SUCCESS;
}