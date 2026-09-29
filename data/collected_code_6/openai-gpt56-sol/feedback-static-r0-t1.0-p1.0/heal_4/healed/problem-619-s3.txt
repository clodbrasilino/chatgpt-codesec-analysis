#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int move_numbers_to_end(char *str, size_t length, size_t capacity)
{
    char *result;
    size_t write_index = 0;

    if (str == NULL || length >= capacity || length == SIZE_MAX) {
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

    for (size_t i = 0; i <= length; ++i) {
        str[i] = result[i];
    }

    free(result);
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch = EOF;

    for (;;) {
        ch = getchar();

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                free(input);
                return EXIT_FAILURE;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
        capacity = 1;
    }

    input[length] = '\0';

    if (move_numbers_to_end(input, length, capacity) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (fwrite(input, sizeof(*input), length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}