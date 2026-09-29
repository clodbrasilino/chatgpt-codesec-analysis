#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_valid_digit_frequencies(const char *input)
{
    size_t frequencies[10] = {0};

    if (input == NULL || *input == '\0') {
        return false;
    }

    for (const unsigned char *p = (const unsigned char *)input; *p != '\0'; ++p) {
        if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
            return false;
        }

        size_t digit = (size_t)(*p - (unsigned char)'0');

        if (frequencies[digit] == digit) {
            return false;
        }

        ++frequencies[digit];
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[47];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
            return EXIT_FAILURE;
        }

        puts("false");
        return EXIT_SUCCESS;
    }

    size_t length = 0;

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n' && input[length] != '\r') {
        ++length;
    }

    if (input[length] == '\n' || input[length] == '\r') {
        input[length] = '\0';
    } else if (input[length] == '\0' && length == sizeof input - 1) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            if (ferror(stdin)) {
                fputs("Input error\n", stderr);
            } else {
                fputs("Input too long\n", stderr);
            }

            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
            return EXIT_FAILURE;
        }
    }

    puts(has_valid_digit_frequencies(input) ? "true" : "false");
    return EXIT_SUCCESS;
}