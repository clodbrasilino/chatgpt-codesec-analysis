#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           ((length == 3U &&
             string[0] == 'a' &&
             string[1] == 'b' &&
             string[2] == 'b') ||
            (length == 4U &&
             string[0] == 'a' &&
             string[1] == 'b' &&
             string[2] == 'b' &&
             string[3] == 'b'));
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int character;
    int result = EXIT_SUCCESS;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0U) {
                new_capacity = 16U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(matches_pattern(input, length) ? "Match" : "No match") == EOF) {
        result = EXIT_FAILURE;
    }

    free(input);
    return result;
}