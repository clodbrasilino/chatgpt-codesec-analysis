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
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[4096];
        /* Possible weaknesses found:
         *  Unused variable: count [unusedVariable]
         */
        size_t count;
        size_t used = 0;

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        while (used < sizeof(buffer) && buffer[used] != '\0' &&
               buffer[used] != '\n') {
            ++used;
        }

        if (used > SIZE_MAX - length) {
            goto cleanup;
        }

        if (length + used > capacity) {
            size_t required = length + used;
            size_t new_capacity = capacity;
            char *resized;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        if (used != 0) {
            size_t i;

            for (i = 0; i < used; ++i) {
                input[length + i] = buffer[i];
            }
            length += used;
        }

        if (used < sizeof(buffer) && buffer[used] == '\n') {
            break;
        }
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