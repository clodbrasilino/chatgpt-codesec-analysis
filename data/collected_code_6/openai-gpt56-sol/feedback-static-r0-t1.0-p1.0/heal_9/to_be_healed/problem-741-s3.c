#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE (1024U * 1024U)

static bool all_characters_same(const unsigned char *data, size_t length)
{
    if (data == NULL || length == 0U) {
        return false;
    }

    for (size_t i = 1U; i < length; ++i) {
        if (data[i] != data[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    unsigned char *input = malloc(MAX_INPUT_SIZE);
    size_t length = 0U;
    bool terminated = false;

    if (input == NULL) {
        fputs("Unable to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    while (length < MAX_INPUT_SIZE) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }
            terminated = true;
            break;
        }

        if (ch == '\n') {
            terminated = true;
            break;
        }

        input[length++] = (unsigned char)ch;
    }

    if (!terminated) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }
        } else if (ch != '\n') {
            fputs("Input exceeds the maximum allowed size.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    if (length == 0U) {
        fputs("No input provided.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    puts(all_characters_same(input, length)
             ? "All characters are the same."
             : "Not all characters are the same.");

    free(input);
    return EXIT_SUCCESS;
}