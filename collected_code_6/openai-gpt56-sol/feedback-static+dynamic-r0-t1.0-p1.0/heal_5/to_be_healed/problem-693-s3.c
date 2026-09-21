#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int remove_multiple_spaces(const char *input, size_t input_len,
                           char **output, size_t *output_len)
{
    char *result;
    size_t read_pos;
    size_t write_pos = 0;
    int previous_space = 0;

    if (input == NULL || output == NULL || output_len == NULL ||
        input_len == SIZE_MAX) {
        return -1;
    }

    *output = NULL;
    *output_len = 0;

    result = malloc(input_len + 1);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0; read_pos < input_len; ++read_pos) {
        unsigned char current = (unsigned char)input[read_pos];

        if (current == (unsigned char)' ') {
            if (previous_space) {
                continue;
            }
            previous_space = 1;
        } else {
            previous_space = 0;
        }

        result[write_pos++] = (char)current;
    }

    result[write_pos] = '\0';
    *output = result;
    *output_len = write_pos;

    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t output_len = 0;
    size_t capacity = 128;
    size_t length = 0;
    int status = EXIT_FAILURE;

    input = malloc(capacity);
    if (input == NULL) {
        goto cleanup;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length >= capacity) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                goto cleanup;
            }

            new_capacity = capacity * 2;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (remove_multiple_spaces(input, length, &output, &output_len) != 0) {
        goto cleanup;
    }

    if (output_len != 0 &&
        fwrite(output, sizeof(*output), output_len, stdout) != output_len) {
        goto cleanup;
    }

    if (fputc('\n', stdout) == EOF || fflush(stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return status;
}