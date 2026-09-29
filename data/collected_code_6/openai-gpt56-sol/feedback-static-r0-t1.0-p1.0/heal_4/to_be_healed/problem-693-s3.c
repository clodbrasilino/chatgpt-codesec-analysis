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
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

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