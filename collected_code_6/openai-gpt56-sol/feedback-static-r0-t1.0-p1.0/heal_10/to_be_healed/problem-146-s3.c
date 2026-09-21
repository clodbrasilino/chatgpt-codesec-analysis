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
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
            }

            unsigned char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        goto cleanup;
    }

    if (length != 0U) {
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