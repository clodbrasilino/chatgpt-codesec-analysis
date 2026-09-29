#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool first_and_last_are_equal(const char *string, size_t length)
{
    return string != NULL &&
           length > 0U &&
           string[0] == string[length - 1U];
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
    while ((character = getchar()) != EOF) {
        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = getchar();

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    free(input);
                    return EXIT_FAILURE;
                }
            }

            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0U) {
                new_capacity = 128U;
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

        input[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin) != 0 || (character == EOF && length == 0U)) {
        free(input);
        return EXIT_FAILURE;
    }

    puts(first_and_last_are_equal(input, length) ? "Equal" : "Not equal");

    free(input);
    return EXIT_SUCCESS;
}