#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool first_and_last_are_equal(const unsigned char *data, size_t length)
{
    return data != NULL && length > 0U && data[0] == data[length - 1U];
}

int main(void)
{
    unsigned char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int character = EOF;

    for (;;) {
        character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin) || length == 0U) {
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            int next = fgetc(stdin);

            if (next == EOF) {
                if (ferror(stdin)) {
                    free(input);
                    return EXIT_FAILURE;
                }
            } else if (next != '\n' && ungetc(next, stdin) == EOF) {
                free(input);
                return EXIT_FAILURE;
            }

            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            unsigned char *resized;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)character;
    }

    puts(first_and_last_are_equal(input, length) ? "Equal" : "Not equal");

    free(input);
    return EXIT_SUCCESS;
}