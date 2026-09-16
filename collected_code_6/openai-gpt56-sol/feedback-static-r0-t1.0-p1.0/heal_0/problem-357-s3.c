#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int find_maximum(const int *records, size_t count, int *maximum)
{
    if (records == NULL || maximum == NULL || count == 0U) {
        return -1;
    }

    int result = records[0];

    for (size_t i = 1U; i < count; ++i) {
        if (records[i] > result) {
            result = records[i];
        }
    }

    *maximum = result;
    return 0;
}

int main(void)
{
    size_t count = 0U;

    if (scanf("%zu", &count) != 1 || count == 0U ||
        count > SIZE_MAX / sizeof(int)) {
        fputs("Invalid record count\n", stderr);
        return EXIT_FAILURE;
    }

    int *records = malloc(count * sizeof(*records));
    if (records == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        long value = 0L;

        errno = 0;
        if (scanf("%ld", &value) != 1 || errno == ERANGE ||
            value < INT_MIN || value > INT_MAX) {
            fputs("Invalid tuple element\n", stderr);
            free(records);
            return EXIT_FAILURE;
        }

        records[i] = (int)value;
    }

    int maximum = 0;
    if (find_maximum(records, count, &maximum) != 0) {
        fputs("Unable to find maximum\n", stderr);
        free(records);
        return EXIT_FAILURE;
    }

    printf("%d\n", maximum);
    free(records);
    return EXIT_SUCCESS;
}