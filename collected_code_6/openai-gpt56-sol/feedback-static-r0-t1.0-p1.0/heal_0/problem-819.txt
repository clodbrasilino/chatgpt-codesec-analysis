#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int count_consecutive_duplicates(const long *numbers, size_t count)
{
    int duplicate_count = 0;

    if (numbers == NULL || count < 2) {
        return 0;
    }

    for (size_t i = 1; i < count; ++i) {
        if (numbers[i] == numbers[i - 1]) {
            if (duplicate_count == INT_MAX) {
                return -1;
            }
            ++duplicate_count;
        }
    }

    return duplicate_count;
}

int main(void)
{
    size_t count = 0;

    if (scanf("%zu", &count) != 1) {
        fprintf(stderr, "Invalid element count.\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(long)) {
        fprintf(stderr, "Element count is too large.\n");
        return EXIT_FAILURE;
    }

    long *numbers = NULL;

    if (count > 0) {
        numbers = malloc(count * sizeof(*numbers));
        if (numbers == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%ld", &numbers[i]) != 1) {
            fprintf(stderr, "Invalid number.\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    int result = count_consecutive_duplicates(numbers, count);

    if (result < 0) {
        fprintf(stderr, "Duplicate count overflow.\n");
        free(numbers);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    free(numbers);

    return EXIT_SUCCESS;
}