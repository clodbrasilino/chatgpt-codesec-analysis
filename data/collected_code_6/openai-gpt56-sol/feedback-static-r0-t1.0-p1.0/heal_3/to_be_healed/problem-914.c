#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

enum { INITIAL_CAPACITY = 128 };

static bool has_two_alternating_characters(const char *string, size_t length)
{
    if (string == NULL || length < 2U || string[0] == string[1]) {
        return false;
    }

    for (size_t i = 2U; i < length; ++i) {
        if (string[i] != string[i % 2U]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0U;
    char *input = malloc(capacity);
    int ch;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity - 1U) {
            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return EXIT_FAILURE;
            }

            size_t new_capacity = capacity * 2U;
            char *resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    puts(has_two_alternating_characters(input, length) ? "Yes" : "No");

    free(input);
    return EXIT_SUCCESS;
}