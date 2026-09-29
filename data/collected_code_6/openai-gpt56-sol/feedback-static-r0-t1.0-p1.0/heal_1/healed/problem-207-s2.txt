#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int longest_repeating_subsequence(const char *str, size_t length,
                                         size_t *result)
{
    size_t columns;
    size_t *previous = NULL;
    size_t *current = NULL;

    if (str == NULL || result == NULL || length == SIZE_MAX) {
        return -1;
    }

    columns = length + 1;

    if (columns > SIZE_MAX / sizeof(*previous)) {
        return -1;
    }

    previous = calloc(columns, sizeof(*previous));
    current = calloc(columns, sizeof(*current));
    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return -1;
    }

    for (size_t i = 1; i <= length; ++i) {
        current[0] = 0;

        for (size_t j = 1; j <= length; ++j) {
            if (str[i - 1] == str[j - 1] && i != j) {
                current[j] = previous[j - 1] + 1;
            } else {
                current[j] = previous[j] > current[j - 1]
                                 ? previous[j]
                                 : current[j - 1];
            }
        }

        size_t *temporary = previous;
        previous = current;
        current = temporary;
    }

    *result = previous[length];

    free(previous);
    free(current);
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t result = 0;
    int character;
    int status = EXIT_FAILURE;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        goto cleanup;
    }

    if (length == 0) {
        result = 0;
    } else if (longest_repeating_subsequence(input, length, &result) != 0) {
        goto cleanup;
    }

    if (printf("%zu\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}