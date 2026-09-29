#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *get_ascii_values(const unsigned char *data, size_t length)
{
    if (data == NULL || length == 0U ||
        length > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *values = malloc(length * sizeof(*values));
    if (values == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < length; ++i) {
        values[i] = (int)data[i];
    }

    return values;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != EOF) {
        if (character == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity;

            if (capacity != 0U) {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            unsigned char *temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0U) {
        free(input);
        return EXIT_SUCCESS;
    }

    int *ascii_values = get_ascii_values(input, length);
    free(input);

    if (ascii_values == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        int result = printf("%d%c", ascii_values[i],
                            i + 1U < length ? ' ' : '\n');
        if (result < 0) {
            free(ascii_values);
            return EXIT_FAILURE;
        }
    }

    free(ascii_values);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}