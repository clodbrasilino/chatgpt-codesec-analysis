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
    int status = EXIT_FAILURE;
    int finished = 0;

    while (!finished) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[4096];
        size_t bytes_read = fread(buffer, 1, sizeof(buffer), stdin);
        size_t i;

        if (bytes_read == 0) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        for (i = 0; i < bytes_read; ++i) {
            unsigned char ch = (unsigned char)buffer[i];

            if (ch == '\n' || ch == '\r') {
                finished = 1;
                break;
            }

            if (length == SIZE_MAX) {
                goto cleanup;
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

                if (new_capacity <= length) {
                    goto cleanup;
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
    }

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