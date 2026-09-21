#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int *get_ascii_values(const unsigned char *string, size_t length)
{
    if (string == NULL || length == 0U ||
        length > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *values = malloc(length * sizeof(*values));
    if (values == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < length; ++i) {
        values[i] = (int)string[i];
    }

    return values;
}

int main(void)
{
    unsigned char *input = NULL;
    int *ascii_values = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int status = EXIT_FAILURE;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        unsigned char buffer[4096];
        size_t count = fread(buffer, 1U, sizeof(buffer), stdin);

        for (size_t i = 0U; i < count; ++i) {
            if (buffer[i] == (unsigned char)'\n') {
                goto input_complete;
            }

            if (length == capacity) {
                size_t required = length + 1U;
                size_t new_capacity = capacity == 0U ? 128U : capacity;

                while (new_capacity < required) {
                    if (new_capacity > SIZE_MAX / 2U) {
                        goto cleanup;
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

            input[length++] = buffer[i];
        }

        if (count < sizeof(buffer)) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            if (feof(stdin)) {
                break;
            }
        }
    }

input_complete:
    if (length > 0U) {
        ascii_values = get_ascii_values(input, length);
        if (ascii_values == NULL) {
            goto cleanup;
        }

        for (size_t i = 0U; i < length; ++i) {
            if (printf("%d%c", ascii_values[i],
                       i + 1U == length ? '\n' : ' ') < 0) {
                goto cleanup;
            }
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(ascii_values);
    free(input);
    return status;
}