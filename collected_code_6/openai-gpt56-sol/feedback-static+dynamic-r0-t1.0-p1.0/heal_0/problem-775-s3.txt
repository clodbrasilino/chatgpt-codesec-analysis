#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool odd_indices_contain_odd_numbers(const int *values, size_t length)
{
    if (values == NULL && length != 0U) {
        return false;
    }

    for (size_t index = 1U; index < length; index += 2U) {
        if (values[index] % 2 == 0) {
            return false;
        }
    }

    return true;
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

    if (length != 0U) {
        values = malloc(length * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t index = 0U; index < length; ++index) {
        if (scanf("%d", &values[index]) != 1) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    puts(odd_indices_contain_odd_numbers(values, length) ? "true" : "false");

    free(values);
    return EXIT_SUCCESS;
}