#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int move_digits_to_end(char *str, size_t capacity)
{
    size_t length;
    size_t write_index = 0;
    char *result;

    if (str == NULL || capacity == 0) {
        return -1;
    }

    length = strnlen(str, capacity);
    if (length == capacity) {
        return -1;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!isdigit((unsigned char)str[i])) {
            result[write_index++] = str[i];
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (isdigit((unsigned char)str[i])) {
            result[write_index++] = str[i];
        }
    }

    result[write_index] = '\0';
    memmove(str, result, write_index + 1);
    free(result);

    return 0;
}

int main(void)
{
    enum {
        INPUT_CAPACITY = 1024,
        DISCARD_CAPACITY = 256
    };

    char *input = malloc(INPUT_CAPACITY);
    size_t length;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, INPUT_CAPACITY, stdin) == NULL) {
        int status = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(input);
        return status;
    }

    length = strnlen(input, INPUT_CAPACITY);
    if (length == INPUT_CAPACITY) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else {
        char discard[DISCARD_CAPACITY];
        int found_newline = 0;

        while (fgets(discard, sizeof discard, stdin) != NULL) {
            size_t discarded_length = strnlen(discard, sizeof discard);

            if (discarded_length == sizeof discard) {
                free(input);
                return EXIT_FAILURE;
            }

            if (discarded_length > 0 &&
                discard[discarded_length - 1] == '\n') {
                found_newline = 1;
                break;
            }
        }

        free(input);

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        if (found_newline || feof(stdin)) {
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    if (move_digits_to_end(input, INPUT_CAPACITY) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}