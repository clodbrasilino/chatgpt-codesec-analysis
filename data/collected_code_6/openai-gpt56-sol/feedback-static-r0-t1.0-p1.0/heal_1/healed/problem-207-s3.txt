#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t longest_repeating_subsequence(const char *str, size_t length)
{
    size_t columns;
    size_t *previous;
    size_t *current;
    size_t result;

    if (str == NULL) {
        return 0;
    }

    if (length == SIZE_MAX ||
        length + 1 > SIZE_MAX / sizeof(*previous)) {
        return 0;
    }

    columns = length + 1;
    previous = calloc(columns, sizeof(*previous));
    current = calloc(columns, sizeof(*current));

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return 0;
    }

    for (size_t i = 1; i <= length; ++i) {
        current[0] = 0;

        for (size_t j = 1; j <= length; ++j) {
            if (i != j && str[i - 1] == str[j - 1]) {
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

    result = previous[length];
    free(previous);
    free(current);

    return result;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    for (;;) {
        character = getchar();

        if (character == '\n' || character == EOF) {
            break;
        }

        if (length == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n",
               longest_repeating_subsequence(input, length)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}