#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_INPUT_LENGTH = 4096 };

static bool matches(const char *str)
{
    if (str == NULL || str[0] != 'a' || str[1] != 'b') {
        return false;
    }

    str += 2;

    while (*str == 'b') {
        ++str;
    }

    return *str == '\0';
}

static bool discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != '\r') {
        if (ch == EOF) {
            return !ferror(stdin);
        }
    }

    return true;
}

int main(void)
{
    char *input = malloc((size_t)MAX_INPUT_LENGTH + 2U);

    if (input == NULL) {
        fputs("Memory allocation error.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, MAX_INPUT_LENGTH + 2, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        input[0] = '\0';
    } else {
        size_t length = strcspn(input, "\r\n");

        if (input[length] == '\0' &&
            length > (size_t)MAX_INPUT_LENGTH) {
            if (discard_line()) {
                fputs("Input is too long.\n", stderr);
            } else {
                fputs("Input error.\n", stderr);
            }

            free(input);
            return EXIT_FAILURE;
        }

        input[length] = '\0';
    }

    puts(matches(input) ? "Match" : "No match");

    free(input);
    return EXIT_SUCCESS;
}