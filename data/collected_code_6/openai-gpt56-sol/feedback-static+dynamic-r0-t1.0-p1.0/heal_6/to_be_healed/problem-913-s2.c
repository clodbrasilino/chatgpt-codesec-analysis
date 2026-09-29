#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 4096 };

static bool ends_with_number(const char *str, size_t length)
{
    return str != NULL &&
           length > 0 &&
           isdigit((unsigned char)str[length - 1]) != 0;
}

int main(void)
{
    char *input = malloc((size_t)MAX_INPUT_LENGTH + 2U);
    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, MAX_INPUT_LENGTH + 2, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        puts("false");
        free(input);
        return EXIT_SUCCESS;
    }

    size_t length = 0;
    while (length < (size_t)MAX_INPUT_LENGTH + 1U &&
           input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > (size_t)MAX_INPUT_LENGTH) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Input is too large.\n", stderr);
        }

        free(input);
        return EXIT_FAILURE;
    }

    puts(ends_with_number(input, length) ? "true" : "false");
    free(input);
    return EXIT_SUCCESS;
}