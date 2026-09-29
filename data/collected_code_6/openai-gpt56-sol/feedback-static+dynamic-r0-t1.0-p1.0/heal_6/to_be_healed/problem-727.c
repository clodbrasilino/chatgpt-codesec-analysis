#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int remove_non_alphanumeric(const char *input, size_t input_len, char **output)
{
    char *result;
    size_t read_pos;
    size_t write_pos = 0;

    if (output == NULL) {
        return -1;
    }

    *output = NULL;

    if ((input == NULL && input_len != 0) || input_len == SIZE_MAX) {
        return -1;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0; read_pos < input_len; ++read_pos) {
        unsigned char ch = (unsigned char)input[read_pos];

        if ((ch >= (unsigned char)'0' && ch <= (unsigned char)'9') ||
            (ch >= (unsigned char)'A' && ch <= (unsigned char)'Z') ||
            (ch >= (unsigned char)'a' && ch <= (unsigned char)'z')) {
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
    int exit_status = EXIT_FAILURE;
    int ch = EOF;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        goto cleanup;
    }

    if (ch == EOF && length == 0) {
        exit_status = EXIT_SUCCESS;
        goto cleanup;
    }

    if (length > 0 && input[length - 1] == '\r') {
        --length;
    }

    if (remove_non_alphanumeric(input, length, &output) != 0) {
        goto cleanup;
    }

    if (puts(output) == EOF) {
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return exit_status;
}