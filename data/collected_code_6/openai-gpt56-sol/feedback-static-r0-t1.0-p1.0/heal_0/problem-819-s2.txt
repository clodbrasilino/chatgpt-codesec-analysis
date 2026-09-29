#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static void count_consecutive_duplicates(const long *numbers, size_t count)
{
    size_t i = 0;

    while (i < count) {
        size_t run_length = 1;

        while (run_length < count - i &&
               numbers[i + run_length] == numbers[i]) {
            ++run_length;
        }

        printf("%ld: %zu\n", numbers[i], run_length);
        i += run_length;
    }
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid element count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count == 0) {
        return EXIT_SUCCESS;
    }

    if (count > SIZE_MAX / sizeof(long)) {
        fputs("Element count is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    long *numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%ld", &numbers[i]) != 1) {
            fputs("Invalid number.\n", stderr);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    count_consecutive_duplicates(numbers, count);
    free(numbers);

    if (ferror(stdout)) {
        fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}