#include <stdio.h>
#include <stdlib.h>

static size_t count_positive(const int *numbers, size_t count)
{
    size_t positive_count = 0U;

    if (numbers == NULL && count != 0U) {
        return 0U;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (numbers[i] > 0) {
            ++positive_count;
        }
    }

    return positive_count;
}

int main(void)
{
    size_t count = 0U;

    if (scanf("%zu", &count) != 1) {
        fprintf(stderr, "Failed to read the list size.\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "List size is too large.\n");
        return EXIT_FAILURE;
    }

    int *numbers = NULL;

    if (count != 0U) {
        numbers = malloc(count * sizeof(*numbers));
        if (numbers == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%d", &numbers[i]) != 1) {
            fprintf(stderr, "Failed to read list element.\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", count_positive(numbers, count));

    free(numbers);
    return EXIT_SUCCESS;
}