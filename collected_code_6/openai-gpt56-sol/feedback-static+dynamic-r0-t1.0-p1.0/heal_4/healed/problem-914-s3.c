#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_two_alternating_characters(const char *str, size_t length)
{
    if (str == NULL || length < 2U || str[0] == str[1]) {
        return false;
    }

    for (size_t i = 2U; i < length; ++i) {
        if (str[i] != str[i % 2U]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int status = EXIT_SUCCESS;
    int character = EOF;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity;

            if (capacity != 0U) {
                if (capacity > SIZE_MAX / 2U) {
                    status = EXIT_FAILURE;
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
            }

            if (new_capacity > SIZE_MAX / sizeof *input) {
                status = EXIT_FAILURE;
                goto cleanup;
            }

            char *new_input = realloc(input, new_capacity * sizeof *input);
            if (new_input == NULL) {
                status = EXIT_FAILURE;
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin) || (character == EOF && length == 0U)) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    puts(has_two_alternating_characters(input, length) ? "Yes" : "No");

cleanup:
    free(input);
    return status;
}