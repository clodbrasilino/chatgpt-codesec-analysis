#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int max_zero_one_difference(const char *string, size_t length,
                                   size_t *start, size_t *end)
{
    int current = 0;
    int maximum = 0;
    size_t current_start = 0;

    *start = 0;
    *end = 0;

    for (size_t i = 0; i < length; ++i) {
        int value;

        if (string[i] == '0') {
            value = 1;
        } else if (string[i] == '1') {
            value = -1;
        } else {
            return -1;
        }

        if (current < 0) {
            current = value;
            current_start = i;
        } else {
            current += value;
        }

        if (current > maximum) {
            maximum = current;
            *start = current_start;
            *end = i;
        }
    }

    return maximum;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = getchar();

        if (character == EOF || character == '\n') {
            break;
        }

        if (character != '0' && character != '1') {
            free(input);
            return EXIT_FAILURE;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin) || length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    size_t start;
    size_t end;
    int result = max_zero_one_difference(input, length, &start, &end);

    free(input);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}