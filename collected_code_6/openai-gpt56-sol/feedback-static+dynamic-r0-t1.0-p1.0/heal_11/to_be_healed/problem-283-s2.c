#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_INPUT_LENGTH = 4096 };

static int frequencies_are_valid(const char *input)
{
    size_t frequencies[10] = {0};

    if (input == NULL || *input == '\0') {
        return 0;
    }

    for (const unsigned char *p = (const unsigned char *)input;
         *p != '\0';
         ++p) {
        if (!isdigit(*p)) {
            return 0;
        }

        size_t digit = (size_t)(*p - (unsigned char)'0');

        if (frequencies[digit] >= digit) {
            return 0;
        }

        ++frequencies[digit];
    }

    return 1;
}

static int consume_line_remainder(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    for (;;) {
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            return ferror(stdin) ? -1 : 0;
        }

        if (strchr(buffer, '\n') != NULL) {
            return 0;
        }
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LENGTH + 2U];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
            return EXIT_FAILURE;
        }

        puts("false");
        return EXIT_SUCCESS;
    }

    char *newline = strchr(input, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(input);

        if (length > (size_t)MAX_INPUT_LENGTH) {
            if (consume_line_remainder() < 0) {
                fputs("Input error\n", stderr);
            } else {
                fputs("Input too long\n", stderr);
            }

            return EXIT_FAILURE;
        }

        if (length == (size_t)MAX_INPUT_LENGTH) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char remainder[2];

            if (fgets(remainder, sizeof remainder, stdin) != NULL) {
                if (remainder[0] != '\n') {
                    if (consume_line_remainder() < 0) {
                        fputs("Input error\n", stderr);
                    } else {
                        fputs("Input too long\n", stderr);
                    }

                    return EXIT_FAILURE;
                }
            } else if (ferror(stdin)) {
                fputs("Input error\n", stderr);
                return EXIT_FAILURE;
            }
        }
    }

    puts(frequencies_are_valid(input) ? "true" : "false");
    return EXIT_SUCCESS;
}