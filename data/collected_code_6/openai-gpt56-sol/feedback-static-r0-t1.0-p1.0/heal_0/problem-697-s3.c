#include <stdio.h>
#include <stdlib.h>

static size_t count_even(const int *values, size_t length)
{
    size_t count = 0;

    if (values == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (values[i] % 2 == 0) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        fputs("List is too large\n", stderr);
        return EXIT_FAILURE;
    }

    int *values = NULL;

    if (length > 0) {
        values = malloc(length * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", count_even(values, length));
    free(values);

    return EXIT_SUCCESS;
}