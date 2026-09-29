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
    size_t write_pos = 0U;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    if (input_len > (SIZE_MAX - 1U) / 2U) {
        return -1;
    }

    capacity = input_len * 2U + 1U;
    result = malloc(capacity);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0U; read_pos < input_len; ++read_pos) {
        unsigned char current = (unsigned char)input[read_pos];

        if (isupper(current) != 0 &&
            read_pos > 0U &&
            input[read_pos - 1U] != ' ') {
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
    size_t length = 0U;
    size_t capacity = 128U;
    int ch;
    int exit_status = EXIT_FAILURE;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        ch = getchar();

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length > SIZE_MAX - 2U) {
            goto cleanup;
        }

        if (length + 1U >= capacity) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                goto cleanup;
            }

            new_capacity = capacity * 2U;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF) {
        if (ferror(stdin) != 0 || length == 0U) {
            goto cleanup;
        }
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