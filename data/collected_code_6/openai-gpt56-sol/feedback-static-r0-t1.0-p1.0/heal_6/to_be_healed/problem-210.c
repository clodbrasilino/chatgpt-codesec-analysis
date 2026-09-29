#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 4096U

static bool contains_only_allowed_characters(const char *string)
{
    const unsigned char *p = (const unsigned char *)string;

    if (string == NULL || *string == '\0') {
        return false;
    }

    while (*p != '\0') {
        if (!((*p >= (unsigned char)'A' && *p <= (unsigned char)'Z') ||
              (*p >= (unsigned char)'a' && *p <= (unsigned char)'z') ||
              (*p >= (unsigned char)'0' && *p <= (unsigned char)'9'))) {
            return false;
        }
        ++p;
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LENGTH + 2U];
    size_t length = 0U;

    if (fgets(input, (int)sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        puts("invalid");
        return EXIT_SUCCESS;
    }

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Input is too large.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    puts(contains_only_allowed_characters(input) ? "valid" : "invalid");
    return EXIT_SUCCESS;
}