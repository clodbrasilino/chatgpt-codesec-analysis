#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int append_byte(char **data, size_t *length, size_t *capacity,
                       unsigned char byte)
{
    char *resized;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;

    if (data == NULL || length == NULL || capacity == NULL ||
        *length > *capacity ||
        (*data == NULL && *capacity != 0)) {
        return -1;
    }

    if (*length == SIZE_MAX) {
        return -1;
    }

    if (*length == *capacity) {
        new_capacity = *capacity;

        if (new_capacity == 0) {
            new_capacity = 128;
        } else if (new_capacity > SIZE_MAX / 2) {
            new_capacity = SIZE_MAX;
        } else {
            new_capacity *= 2;
        }

        if (new_capacity <= *length) {
            return -1;
        }

        resized = realloc(*data, new_capacity);
        if (resized == NULL) {
            return -1;
        }

        *data = resized;
        *capacity = new_capacity;
    }

    (*data)[*length] = (char)byte;
    ++*length;

    return 0;
}

static int remove_multiple_spaces(const char *input, size_t input_len,
                                  char **output, size_t *output_len)
{
    char *result;
    size_t read_pos;
    size_t write_pos = 0;
    int previous_space = 0;

    if (output == NULL || output_len == NULL ||
        (input == NULL && input_len != 0) ||
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
            if (previous_space != 0) {
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
    size_t input_len = 0;
    size_t input_capacity = 0;
    size_t output_len = 0;
    int status = EXIT_FAILURE;
    int current;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((current = getchar()) != EOF) {
        if (current == '\n') {
            break;
        }

        if (append_byte(&input, &input_len, &input_capacity,
                        (unsigned char)current) != 0) {
            goto cleanup;
        }
    }

    if (current == EOF && ferror(stdin) != 0) {
        goto cleanup;
    }

    if (remove_multiple_spaces(input, input_len, &output, &output_len) != 0) {
        goto cleanup;
    }

    if (output_len != 0 &&
        fwrite(output, 1, output_len, stdout) != output_len) {
        goto cleanup;
    }

    if (putchar('\n') == EOF || fflush(stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return status;
}