#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_substrings(const unsigned char *data, size_t length,
                            size_t *result)
{
    size_t frequencies[256] = {0};
    size_t total = 0;

    if ((data == NULL && length != 0U) || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t frequency = frequencies[data[i]];

        if (frequency == SIZE_MAX || total > SIZE_MAX - frequency - 1U) {
            return -1;
        }

        total += frequency + 1U;
        frequencies[data[i]] = frequency + 1U;
    }

    *result = total;
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t count = 0;
    int status = EXIT_FAILURE;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        unsigned char buffer[4096];
        size_t bytes_read = fread(buffer, 1U, sizeof buffer, stdin);
        size_t line_bytes = 0;

        while (line_bytes < bytes_read && buffer[line_bytes] != '\n') {
            ++line_bytes;
        }

        if (line_bytes != 0U) {
            if (length > SIZE_MAX - line_bytes) {
                goto cleanup;
            }

            size_t required = length + line_bytes;

            if (required > capacity) {
                size_t new_capacity = capacity == 0U ? 64U : capacity;

                while (new_capacity < required) {
                    if (new_capacity > SIZE_MAX / 2U) {
                        new_capacity = required;
                        break;
                    }
                    new_capacity *= 2U;
                }

                unsigned char *new_input = realloc(input, new_capacity);
                if (new_input == NULL) {
                    goto cleanup;
                }

                input = new_input;
                capacity = new_capacity;
            }

            for (size_t i = 0; i < line_bytes; ++i) {
                input[length + i] = buffer[i];
            }
            length += line_bytes;
        }

        if (line_bytes < bytes_read) {
            break;
        }

        if (bytes_read < sizeof buffer) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }
    }

    if (count_substrings(input, length, &count) != 0) {
        goto cleanup;
    }

    if (printf("%zu\n", count) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}