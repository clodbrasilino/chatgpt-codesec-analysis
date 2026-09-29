#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int min_size(size_t a, size_t b, size_t *result)
{
    if (result == NULL) {
        return -1;
    }

    *result = a < b ? a : b;
    return 0;
}

int main(void)
{
    size_t first_length;
    size_t second_length;
    size_t minimum_length;

    if (scanf("%zu %zu", &first_length, &second_length) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (min_size(first_length, second_length, &minimum_length) != 0) {
        fputs("Unable to determine the minimum length\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", minimum_length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}