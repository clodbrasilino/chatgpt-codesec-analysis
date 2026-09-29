#include <stdio.h>
#include <stdlib.h>

static int read_size(size_t *size)
{
    unsigned long long input;

    if (scanf("%llu", &input) != 1 || input > SIZE_MAX / sizeof(int)) {
        return 0;
    }

    *size = (size_t)input;
    return 1;
}

static void print_frequencies(const int *values, size_t size)
{
    unsigned char *counted = calloc(size, sizeof(*counted));

    if (counted == NULL && size != 0) {
        fputs("Memory allocation failed\n", stderr);
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        if (counted[i] != 0) {
            continue;
        }

        size_t frequency = 1;

        for (size_t j = i + 1; j < size; ++j) {
            if (values[j] == values[i]) {
                ++frequency;
                counted[j] = 1;
            }
        }

        printf("%d: %zu\n", values[i], frequency);
    }

    free(counted);
}

int main(void)
{
    size_t size;

    if (!read_size(&size)) {
        fputs("Invalid list size\n", stderr);
        return EXIT_FAILURE;
    }

    int *values = NULL;

    if (size != 0) {
        values = malloc(size * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < size; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fputs("Invalid element\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    print_frequencies(values, size);
    free(values);

    return EXIT_SUCCESS;
}