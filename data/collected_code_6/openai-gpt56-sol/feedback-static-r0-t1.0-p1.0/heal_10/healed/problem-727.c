#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

int remove_non_alphanumeric(const char *input, size_t input_len, char **output)
{
    char *result;
    size_t read_pos;
    size_t write_pos = 0;

    if (input == NULL || output == NULL || input_len == SIZE_MAX) {
        return -1;
    }

    *output = NULL;

    result = malloc(input_len + 1);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0; read_pos < input_len; ++read_pos) {
        unsigned char ch = (unsigned char)input[read_pos];

        if (isalnum(ch) != 0) {
            result[write_pos++] = (char)ch;
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
    size_t capacity = 0;
    size_t length = 0;
    int status = EXIT_FAILURE;

    for (;;) {
        int ch;

        ch = fgetc(stdin);
        if (ch == EOF) {
            if (ferror(stdin) != 0) {
                goto cleanup;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *temporary;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity <= SIZE_MAX / 2) {
                new_capacity = capacity * 2;
            } else {
                new_capacity = required;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                goto cleanup;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            goto cleanup;
        }
    }

    input[length] = '\0';

    if (remove_non_alphanumeric(input, length, &output) != 0) {
        goto cleanup;
    }

    if (puts(output) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return status;
}