#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE (1024U * 1024U)

static bool all_characters_same(const unsigned char *str, size_t length)
{
    if (str == NULL || length == 0U) {
        return false;
    }

    for (size_t i = 1U; i < length; ++i) {
        if (str[i] != str[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    unsigned char *input = malloc(MAX_INPUT_SIZE);
    size_t length = 0U;
    int ch;

    if (input == NULL) {
        fputs("Unable to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    while (length < MAX_INPUT_SIZE) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (length == MAX_INPUT_SIZE) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch != EOF && ch != '\n') {
            fputs("Input exceeds the maximum allowed size.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (length == 0U && ch == EOF) {
        fputs("No input provided.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    puts(all_characters_same(input, length)
             ? "All characters are the same."
             : "Not all characters are the same.");

    free(input);
    return EXIT_SUCCESS;
}