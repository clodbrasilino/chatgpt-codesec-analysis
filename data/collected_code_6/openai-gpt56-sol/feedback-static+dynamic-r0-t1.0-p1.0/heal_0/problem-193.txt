#include <stdio.h>
#include <stdlib.h>

static int remove_duplicates(const int *input, size_t length, int **output, size_t *output_length)
{
    int *result = NULL;
    size_t unique_count = 0;

    if (output == NULL || output_length == NULL || (input == NULL && length != 0)) {
        return -1;
    }

    *output = NULL;
    *output_length = 0;

    if (length == 0) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = malloc(length * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t j = 0;

        while (j < unique_count && result[j] != input[i]) {
            ++j;
        }

        if (j == unique_count) {
            result[unique_count++] = input[i];
        }
    }

    *output = result;
    *output_length = unique_count;
    return 0;
}

int main(void)
{
    int tuple[] = {1, 2, 2, 3, 4, 3, 5, 1};
    const size_t tuple_length = sizeof(tuple) / sizeof(tuple[0]);
    int *unique = NULL;
    size_t unique_length = 0;

    if (remove_duplicates(tuple, tuple_length, &unique, &unique_length) != 0) {
        fputs("Failed to remove duplicates.\n", stderr);
        return EXIT_FAILURE;
    }

    putchar('(');
    for (size_t i = 0; i < unique_length; ++i) {
        if (i != 0) {
            fputs(", ", stdout);
        }
        printf("%d", unique[i]);
    }
    puts(")");

    free(unique);
    return EXIT_SUCCESS;
}