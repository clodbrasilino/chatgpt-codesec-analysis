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
    int character;
    int *ascii_values;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && length == 0U) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0U) {
        free(input);
        return EXIT_SUCCESS;
    }

    ascii_values = get_ascii_values(input, length);
    free(input);

    if (ascii_values == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        printf("%d%s", ascii_values[i], (i + 1U < length) ? " " : "\n");
    }

    free(ascii_values);
    return EXIT_SUCCESS;
}