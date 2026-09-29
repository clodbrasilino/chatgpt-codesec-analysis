#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int remove_multiple_spaces(const char *input, size_t input_len, char **output)
{
    char *result;
    size_t read_pos;
    size_t write_pos;

    if (input == NULL || output == NULL || input_len == SIZE_MAX) {
        return -1;
    }

    *output = NULL;

    result = malloc(input_len + 1);
    if (result == NULL) {
        return -1;
    }

    read_pos = 0;
    write_pos = 0;

    while (read_pos < input_len) {
        if (input[read_pos] == ' ') {
            result[write_pos++] = ' ';
            do {
                ++read_pos;
            } while (read_pos < input_len && input[read_pos] == ' ');
        } else {
            result[write_pos++] = input[read_pos++];
        }
    }

    result[write_pos] = '\0';
    *output = result;
    return 0;
}

int main(void)
{
    char *input;
    char *output;
    size_t length;
    size_t capacity;
    int ch;

    input = NULL;
    output = NULL;
    length = 0;
    capacity = 0;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > (SIZE_MAX - 1) / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return EXIT_SUCCESS;
    }

    if (remove_multiple_spaces(input, length, &output) != 0) {
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