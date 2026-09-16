#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

int *get_lucid_numbers(int n, size_t *count);

int *get_lucid_numbers(int n, size_t *count)
{
    if (count == NULL || n < 1) {
        return NULL;
    }
    if ((size_t)n > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    size_t len = (size_t)n;
    int *arr = malloc(len * sizeof *arr);
    if (arr == NULL) {
        return NULL;
    }

    int *result = malloc(len * sizeof *result);
    if (result == NULL) {
        free(arr);
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        arr[i] = (int)(i + 1);
    }

    size_t rcount = 0;
    result[rcount++] = arr[0];

    size_t start = 1;
    while (start < len) {
        int step = arr[start];
        result[rcount++] = step;

        size_t write = start;
        size_t idx = 0;
        for (size_t read = start; read < len; read++, idx++) {
            if (idx % (size_t)step != 0) {
                arr[write++] = arr[read];
            }
        }
        len = write;
    }

    free(arr);

    int *shrunk = realloc(result, rcount * sizeof *shrunk);
    if (shrunk != NULL) {
        result = shrunk;
    }

    *count = rcount;
    return result;
}

int main(int argc, const char *const argv[])
{
    int n = 25;

    if (argc > 1) {
        char *end = NULL;
        errno = 0;
        long value = strtol(argv[1], &end, 10);
        if (errno != 0 || end == argv[1] || *end != '\0' ||
            value < 1 || value > INT_MAX) {
            fprintf(stderr, "Invalid input: expected a positive integer\n");
            return EXIT_FAILURE;
        }
        n = (int)value;
    }

    size_t count = 0;
    int *lucid = get_lucid_numbers(n, &count);
    if (lucid == NULL) {
        fprintf(stderr, "Failed to compute lucid numbers\n");
        return EXIT_FAILURE;
    }

    printf("Lucid numbers <= %d:\n", n);
    for (size_t i = 0; i < count; i++) {
        printf("%d ", lucid[i]);
    }
    printf("\n");

    free(lucid);
    return EXIT_SUCCESS;
}