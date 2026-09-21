#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *get_ascii_values(const unsigned char *data, size_t length)
{
    if (data == NULL || length == 0U ||
        length > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *values = malloc(length * sizeof(*values));
    if (values == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < length; ++i) {
        values[i] = (int)data[i];
    }

    return values;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int character = 0;

    for (;;) {
        character = getchar();

        if (character == EOF || character == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            unsigned char *temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length] = (unsigned char)character;
        ++length;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0U) {
        free(input);
        return character == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    int *ascii_values = get_ascii_values(input, length);
    free(input);

    if (ascii_values == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        const int separator = (i < length - 1U) ? ' ' : '\n';

        if (printf("%d%c", ascii_values[i], separator) < 0) {
            free(ascii_values);
            return EXIT_FAILURE;
        }
    }

    free(ascii_values);
    return EXIT_SUCCESS;
}