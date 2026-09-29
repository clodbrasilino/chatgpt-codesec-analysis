#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int count_consecutive_duplicates(const long *numbers, size_t count)
{
    int duplicates = 0;

    if (numbers == NULL && count != 0U) {
        return -1;
    }

    for (size_t i = 1U; i < count; ++i) {
        if (numbers[i] == numbers[i - 1U]) {
            ++duplicates;
        }
    }

    return duplicates;
}

int main(void)
{
    size_t count = 0U;

    if (scanf("%zu", &count) != 1) {
        fprintf(stderr, "Invalid element count.\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(long)) {
        fprintf(stderr, "Element count is too large.\n");
        return EXIT_FAILURE;
    }

    long *numbers = NULL;

    if (count != 0U) {
        numbers = malloc(count * sizeof(*numbers));
        if (numbers == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%ld", &numbers[i]) != 1) {
            fprintf(stderr, "Invalid number at position %zu.\n", i);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    int result = count_consecutive_duplicates(numbers, count);
    if (result < 0) {
        fprintf(stderr, "Unable to count duplicates.\n");
        free(numbers);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    free(numbers);

    return EXIT_SUCCESS;
}