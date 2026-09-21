#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 1024 * 1024 };

static bool first_and_last_equal(const char *str, size_t length)
{
    return str != NULL && length > 0 && str[0] == str[length - 1];
}

int main(void)
{
    char *input = malloc((size_t)MAX_INPUT_LENGTH + 1);
    size_t length = 0;
    int ch;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length >= (size_t)MAX_INPUT_LENGTH) {
            free(input);
            return EXIT_FAILURE;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    puts(first_and_last_equal(input, length) ? "Equal" : "Not equal");

    free(input);
    return EXIT_SUCCESS;
}