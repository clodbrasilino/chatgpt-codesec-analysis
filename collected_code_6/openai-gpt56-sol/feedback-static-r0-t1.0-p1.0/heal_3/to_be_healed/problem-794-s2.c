#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2U &&
           string[0] == 'a' &&
           string[length - 1U] == 'b';
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' &&
           character != '\r' &&
           character != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;
            char *resized;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return 1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == '\r') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = getchar();

        if (next != '\n' && next != EOF) {
            ungetc(next, stdin);
        }
    }

    if (ferror(stdin)) {
        free(input);
        return 1;
    }

    if (matches_pattern(input, length)) {
        puts("Match");
    } else {
        puts("No match");
    }

    free(input);
    return 0;
}