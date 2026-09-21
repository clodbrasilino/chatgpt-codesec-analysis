#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int remove_multiple_spaces(const char *input, size_t input_len, char **output)
{
    char *result;
    size_t read_pos = 0;
    size_t write_pos = 0;

    if (output == NULL) {
        return -1;
    }

    *output = NULL;

    if (input == NULL && input_len != 0) {
        return -1;
    }

    if (input_len == SIZE_MAX) {
        return -1;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        return -1;
    }

    while (read_pos < input_len) {
        char current = input[read_pos++];

        result[write_pos++] = current;

        if (current == ' ') {
            while (read_pos < input_len && input[read_pos] == ' ') {
                ++read_pos;
            }
        }
    }

    result[write_pos] = '\0';
    *output = result;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int status = EXIT_FAILURE;

    for (;;) {
        char buffer[4096];
        size_t count = fread(buffer, 1, sizeof(buffer), stdin);
        size_t used = 0;

        while (used < count) {
            size_t line_count = 0;
            char *new_input;
            size_t required;
            size_t new_capacity;

            while (line_count < count - used &&
                   buffer[used + line_count] != '\n') {
                ++line_count;
            }

            if (line_count > SIZE_MAX - length) {
                goto cleanup;
            }

            required = length + line_count;
            if (required > capacity) {
                new_capacity = capacity == 0 ? 128 : capacity;

                while (new_capacity < required) {
                    if (new_capacity > SIZE_MAX / 2) {
                        new_capacity = required;
                        break;
                    }
                    new_capacity *= 2;
                }

                if (new_capacity < required) {
                    goto cleanup;
                }

                new_input = realloc(input, new_capacity);
                if (new_input == NULL) {
                    goto cleanup;
                }

                input = new_input;
                capacity = new_capacity;
            }

            if (line_count != 0) {
                size_t i;

                for (i = 0; i < line_count; ++i) {
                    input[length + i] = buffer[used + i];
                }
                length = required;
            }

            used += line_count;

            if (used < count && buffer[used] == '\n') {
                goto input_complete;
            }
        }

        if (count < sizeof(buffer)) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }
    }

input_complete:
    if (remove_multiple_spaces(input, length, &output) != 0) {
        goto cleanup;
    }

    if (fputs(output, stdout) == EOF || fputc('\n', stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return status;
}