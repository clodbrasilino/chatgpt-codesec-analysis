#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_spaces_before_capitals(const char *input, size_t input_len,
                                      char **output)
{
    char *result;
    size_t capacity;
    size_t read_pos;
    size_t write_pos = 0;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    if (input_len > (SIZE_MAX - 1) / 2) {
        return -1;
    }

    capacity = input_len * 2 + 1;
    result = malloc(capacity);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0; read_pos < input_len; ++read_pos) {
        unsigned char current = (unsigned char)input[read_pos];

        if (isupper(current) &&
            read_pos > 0 &&
            input[read_pos - 1] != ' ') {
            result[write_pos++] = ' ';
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
    char *output = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;
    int exit_status = EXIT_FAILURE;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *new_input;
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length) {
                new_capacity = length + 1;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        goto cleanup;
    }

    if (capacity == 0) {
        input = malloc(1);
        if (input == NULL) {
            goto cleanup;
        }
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = 1;
    }

    input[length] = '\0';

    if (add_spaces_before_capitals(input, length, &output) != 0) {
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