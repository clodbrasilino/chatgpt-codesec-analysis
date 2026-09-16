#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static size_t remove_duplicates(int *values, size_t length)
{
    size_t unique_count = 0;

    for (size_t i = 0; i < length; ++i) {
        size_t j = 0;

        while (j < unique_count && values[j] != values[i]) {
            ++j;
        }

        if (j == unique_count) {
            values[unique_count++] = values[i];
        }
    }

    return unique_count;
}

int main(void)
{
    size_t list_count;

    if (scanf("%zu", &list_count) != 1) {
        fprintf(stderr, "Failed to read the number of lists.\n");
        return EXIT_FAILURE;
    }

    for (size_t list_index = 0; list_index < list_count; ++list_index) {
        size_t length;

        if (scanf("%zu", &length) != 1) {
            fprintf(stderr, "Failed to read a list length.\n");
            return EXIT_FAILURE;
        }

        if (length > SIZE_MAX / sizeof(int)) {
            fprintf(stderr, "List is too large.\n");
            return EXIT_FAILURE;
        }

        int *values = NULL;

        if (length > 0) {
            values = malloc(length * sizeof(*values));
            if (values == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                return EXIT_FAILURE;
            }
        }

        for (size_t i = 0; i < length; ++i) {
            if (scanf("%d", &values[i]) != 1) {
                fprintf(stderr, "Failed to read a list element.\n");
                free(values);
                return EXIT_FAILURE;
            }
        }

        size_t new_length = remove_duplicates(values, length);

        for (size_t i = 0; i < new_length; ++i) {
            if (i > 0) {
                putchar(' ');
            }
            printf("%d", values[i]);
        }
        putchar('\n');

        free(values);
    }

    return EXIT_SUCCESS;
}