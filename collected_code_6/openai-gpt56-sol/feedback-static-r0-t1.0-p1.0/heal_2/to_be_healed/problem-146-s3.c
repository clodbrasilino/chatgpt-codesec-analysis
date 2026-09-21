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
    int *ascii_values;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    ascii_values = get_ascii_values(input, length);
    if (ascii_values == NULL && length != 0U) {
        free(input);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (printf("%d%s", ascii_values[i],
                   (i + 1U < length) ? " " : "\n") < 0) {
            free(ascii_values);
            free(input);
            return EXIT_FAILURE;
        }
    }

    free(ascii_values);
    free(input);
    return EXIT_SUCCESS;
}