#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  */

static bool all_characters_same(const char *str)
{
    if (str == NULL || str[0] == '\0') {
        return false;
    }

    for (size_t i = 1; str[i] != '\0'; ++i) {
        if (str[i] != str[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == capacity) {
            if (capacity > (SIZE_MAX - 1) / 2) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\r') {
        --length;
    }

    if (length == SIZE_MAX) {
        free(input);
        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    char *terminated_input = realloc(input, length + 1);
    if (terminated_input == NULL) {
        free(input);
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    input = terminated_input;
    input[length] = '\0';

    puts(all_characters_same(input) ? "True" : "False");

    free(input);
    return EXIT_SUCCESS;
}