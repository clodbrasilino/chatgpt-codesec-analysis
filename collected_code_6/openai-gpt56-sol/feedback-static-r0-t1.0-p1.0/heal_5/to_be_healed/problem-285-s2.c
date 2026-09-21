#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length == capacity) {
            new_capacity = capacity == 0U ? 16U : capacity * 2U;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
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