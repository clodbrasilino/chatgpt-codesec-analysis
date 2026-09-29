#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int longest_repeating_subsequence(const unsigned char *str,
                                         size_t length,
                                         size_t *result)
{
    if (result == NULL || (str == NULL && length != 0) ||
        length == SIZE_MAX ||
        length + 1 > SIZE_MAX / sizeof(size_t)) {
        return 0;
    }

    size_t columns = length + 1;
    size_t *previous = calloc(columns, sizeof(*previous));
    size_t *current = calloc(columns, sizeof(*current));

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

    *result = previous[length];

    free(previous);
    free(current);
    return 1;
}

static int read_line(unsigned char **buffer, size_t *length)
{
    if (buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0;
    size_t capacity = 0;

    for (;;) {
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                free(*buffer);
                *buffer = NULL;
                *length = 0;
                return 0;
            }
            return 1;
        }

        if (character == '\n') {
            return 1;
        }

        if (*length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(*buffer);
                    *buffer = NULL;
                    *length = 0;
                    return 0;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= *length) {
                free(*buffer);
                *buffer = NULL;
                *length = 0;
                return 0;
            }

            unsigned char *resized = realloc(*buffer, new_capacity);
            if (resized == NULL) {
                free(*buffer);
                *buffer = NULL;
                *length = 0;
                return 0;
            }

            *buffer = resized;
            capacity = new_capacity;
        }

        (*buffer)[(*length)++] = (unsigned char)character;
    }
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t result = 0;

    if (!read_line(&input, &length)) {
        return EXIT_FAILURE;
    }

    if (!longest_repeating_subsequence(input, length, &result)) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}