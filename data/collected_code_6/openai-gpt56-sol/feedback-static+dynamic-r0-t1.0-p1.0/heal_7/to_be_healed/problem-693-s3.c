#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int append_bytes(char **data, size_t *length, size_t *capacity,
                        const char *source, size_t count)
{
    size_t required;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;
    char *resized;

    if (data == NULL || length == NULL || capacity == NULL ||
        (source == NULL && count != 0)) {
        return -1;
    }

    if (count > SIZE_MAX - *length) {
        return -1;
    }

    required = *length + count;
    if (required > *capacity) {
        new_capacity = *capacity;

        if (new_capacity == 0) {
            new_capacity = 128;
        }

        while (new_capacity < required) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = required;
                break;
            }
            new_capacity *= 2;
        }

        resized = realloc(*data, new_capacity);
        if (resized == NULL) {
            return -1;
        }

        *data = resized;
        *capacity = new_capacity;
    }

    if (count != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(*data + *length, source, count);
        *length = required;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t input_len = 0;
    size_t input_capacity = 0;
    size_t output_len = 0;
    int status = EXIT_FAILURE;
    int current;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((current = fgetc(stdin)) != EOF) {
        char byte;

        if (current == '\n') {
            break;
        }

        byte = (char)(unsigned char)current;
        if (append_bytes(&input, &input_len, &input_capacity, &byte, 1) != 0) {
            goto cleanup;
        }
    }

    if (current == EOF && ferror(stdin)) {
        goto cleanup;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            goto cleanup;
        }
    }

    if (remove_multiple_spaces(input, input_len, &output, &output_len) != 0) {
        goto cleanup;
    }

    if (output_len != 0 &&
        fwrite(output, 1, output_len, stdout) != output_len) {
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