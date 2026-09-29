#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int move_numbers_to_end(char *str, size_t capacity)
{
    size_t length;
    size_t position = 0;
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
            result[position++] = str[i];
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (isdigit((unsigned char)str[i])) {
            result[position++] = str[i];
        }
    }

    result[position] = '\0';
    memcpy(str, result, position + 1);
    free(result);

    return 0;
}

int main(void)
{
    enum { INPUT_CAPACITY = 1024 };
    char *input = malloc(INPUT_CAPACITY);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, INPUT_CAPACITY, stdin) == NULL) {
        free(input);
        return EXIT_FAILURE;
    }

    size_t length = strnlen(input, INPUT_CAPACITY);
    if (length == INPUT_CAPACITY) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';

        if (length > 0 && input[length - 1] == '\r') {
            input[--length] = '\0';
        }
    } else if (!feof(stdin)) {
        char discard[256];
        int line_too_long = 0;

        do {
            if (fgets(discard, sizeof discard, stdin) == NULL) {
                break;
            }

            line_too_long = 1;
        } while (strchr(discard, '\n') == NULL);

        if (ferror(stdin) || line_too_long) {
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (move_numbers_to_end(input, INPUT_CAPACITY) != 0) {
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