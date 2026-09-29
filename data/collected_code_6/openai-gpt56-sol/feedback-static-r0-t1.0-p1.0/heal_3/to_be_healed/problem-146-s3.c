#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *get_ascii_values(const char *string, size_t length)
{
    int *values;

    if (string == NULL || length == 0U) {
        return NULL;
    }

    if (length > SIZE_MAX / sizeof(*values)) {
        return NULL;
    }

    values = malloc(length * sizeof(*values));
    if (values == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < length; ++i) {
        values[i] = (unsigned char)string[i];
    }

    return values;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int *ascii_values = NULL;
    int character;
    int status = EXIT_FAILURE;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();

        if (character == '\n' || character == EOF) {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        goto cleanup;
    }

    if (length > 0U) {
        ascii_values = get_ascii_values(input, length);
        if (ascii_values == NULL) {
            goto cleanup;
        }
    }

    for (size_t i = 0U; i < length; ++i) {
        if (printf("%d%c", ascii_values[i],
                   i + 1U < length ? ' ' : '\n') < 0) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(ascii_values);
    free(input);
    return status;
}