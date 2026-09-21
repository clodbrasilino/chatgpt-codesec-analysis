#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int add_spaces_before_capitals(const char *input, size_t input_len,
                                      char **output)
{
    size_t extra_spaces = 0;
    size_t capacity;
    size_t read_pos;
    size_t write_pos = 0;
    char *result;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    for (read_pos = 1; read_pos < input_len; ++read_pos) {
        unsigned char previous = (unsigned char)input[read_pos - 1];
        unsigned char current = (unsigned char)input[read_pos];

        if (((previous >= 'a' && previous <= 'z') ||
             (previous >= '0' && previous <= '9')) &&
            current >= 'A' && current <= 'Z') {
            ++extra_spaces;
        }
    }

    if (input_len > SIZE_MAX - extra_spaces - 1U) {
        return -1;
    }

    capacity = input_len + extra_spaces + 1U;
    result = malloc(capacity);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0; read_pos < input_len; ++read_pos) {
        if (read_pos > 0) {
            unsigned char previous = (unsigned char)input[read_pos - 1];
            unsigned char current = (unsigned char)input[read_pos];

            if (((previous >= 'a' && previous <= 'z') ||
                 (previous >= '0' && previous <= '9')) &&
                current >= 'A' && current <= 'Z') {
                result[write_pos++] = ' ';
            }
        }

        result[write_pos++] = input[read_pos];
    }

    result[write_pos] = '\0';
    *output = result;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    char *output = NULL;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length == SIZE_MAX - 1U) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= length + 1U) {
                new_capacity = length + 2U;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0U) {
        free(input);
        return EXIT_SUCCESS;
    }

    if (input == NULL) {
        input = malloc(1U);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
        capacity = 1U;
    } else if (length == capacity) {
        char *resized;

        if (capacity == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        resized = realloc(input, capacity + 1U);
        if (resized == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = resized;
    }

    input[length] = '\0';

    if (add_spaces_before_capitals(input, length, &output) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}