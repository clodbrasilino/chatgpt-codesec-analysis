#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum { INPUT_SIZE = 1024 };

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2U &&
           string[0] == 'a' &&
           string[length - 1U] == 'b';
}

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    if (ferror(stdin)) {
        perror("fgetc");
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE + 2U];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return 1;
        }

        puts("No match");
        return 0;
    }

    size_t length = 0U;

    while (length < sizeof input &&
           input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (length == sizeof input) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] == '\r') {
        input[length] = '\0';

        if (length + 1U < sizeof input && input[length + 1U] == '\n') {
            input[length + 1U] = '\0';
        } else if (discard_line() != 0) {
            return 1;
        }
    } else {
        int ch;

        if (length > INPUT_SIZE) {
            if (discard_line() != 0) {
                return 1;
            }

            fputs("Input exceeds maximum length\n", stderr);
            return 1;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            if (discard_line() != 0) {
                return 1;
            }

            fputs("Input exceeds maximum length\n", stderr);
            return 1;
        }

        if (ferror(stdin)) {
            perror("fgetc");
            return 1;
        }
    }

    if (length > INPUT_SIZE) {
        fputs("Input exceeds maximum length\n", stderr);
        return 1;
    }

    input[length] = '\0';
    puts(matches_pattern(input, length) ? "Match" : "No match");

    return 0;
}