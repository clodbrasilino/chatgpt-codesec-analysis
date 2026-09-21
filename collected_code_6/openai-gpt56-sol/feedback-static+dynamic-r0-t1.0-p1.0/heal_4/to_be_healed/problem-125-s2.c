#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

static intmax_t max_zero_one_difference(const char *string,
                                        size_t *start,
                                        size_t *end)
{
    intmax_t current = 0;
    intmax_t maximum = 0;
    size_t current_start = 0;

    *start = 0;
    *end = 0;

    for (size_t i = 0; string[i] != '\0'; ++i) {
        intmax_t value;

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

        if (character == '\n' || character == EOF) {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(input);
            return EXIT_FAILURE;
        }

        if (capacity <= length + 1) {
            size_t required = length + 2;
            size_t new_capacity = capacity == 0 ? 64 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
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

    input[length] = '\0';

    size_t start;
    size_t end;
    intmax_t result = max_zero_one_difference(input, &start, &end);

    free(input);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    if (printf("%jd\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}