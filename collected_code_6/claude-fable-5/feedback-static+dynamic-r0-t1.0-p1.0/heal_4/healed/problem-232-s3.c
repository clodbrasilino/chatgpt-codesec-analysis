#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

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
    size_t copy_bytes;
    size_t result_bytes;
    size_t i;

    if (data == NULL || result == NULL) {
        return -1;
    }
    if (size == 0U || n == 0U || n > size) {
        return -1;
    }
    if (size > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    copy_bytes = size * sizeof(int);
    result_bytes = n * sizeof(int);

    if (result_bytes > copy_bytes) {
        return -1;
    }

    copy = malloc(copy_bytes);
    if (copy == NULL) {
        return -1;
    }

    for (i = 0U; i < size; i++) {
        copy[i] = data[i];
    }

    qsort(copy, size, sizeof(int), compare_desc);

    for (i = 0U; i < n; i++) {
        result[i] = copy[i];
    }

    free(copy);

    return 0;
}

int main(int argc, char *const argv[])
{
    int dataset[] = { 42, 7, 93, 15, 88, 3, 61, 27, 54, 99 };
    size_t size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n;
    unsigned long parsed;
    char *endptr;
    int *largest;
    size_t i;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoul(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid number: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (parsed == 0UL || parsed > (unsigned long)size) {
        fprintf(stderr, "Invalid request size\n");
        return EXIT_FAILURE;
    }

    n = (size_t)parsed;

    if (n > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Invalid request size\n");
        return EXIT_FAILURE;
    }

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