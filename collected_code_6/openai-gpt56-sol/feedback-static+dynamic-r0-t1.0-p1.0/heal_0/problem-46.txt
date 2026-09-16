#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool all_numbers_different(const long *numbers, size_t count)
{
    if (numbers == NULL && count != 0U) {
        return false;
    }

    for (size_t i = 0U; i < count; ++i) {
        for (size_t j = i + 1U; j < count; ++j) {
            if (numbers[i] == numbers[j]) {
                return false;
            }
        }
    }

    return true;
}

static bool read_size(size_t *count)
{
    unsigned long long value;

    if (count == NULL || scanf("%llu", &value) != 1) {
        return false;
    }

    if (value > (unsigned long long)SIZE_MAX) {
        return false;
    }

    *count = (size_t)value;
    return true;
}

int main(void)
{
    size_t count;

    if (!read_size(&count)) {
        fputs("Invalid number count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(long)) {
        fputs("Number count is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    long *numbers = NULL;

    if (count != 0U) {
        numbers = malloc(count * sizeof(*numbers));
        if (numbers == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%ld", &numbers[i]) != 1) {
            fputs("Invalid input.\n", stderr);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    puts(all_numbers_different(numbers, count) ? "All numbers are different."
                                               : "Some numbers are equal.");

    free(numbers);
    return EXIT_SUCCESS;
}