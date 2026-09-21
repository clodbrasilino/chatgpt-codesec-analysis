#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>

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

        size_t i = 0;
        while (buffer[i] != '\0') {
            if (buffer[i] == '\n') {
                return 0;
            }
            ++i;
        }
    }
}

int main(void)
{
    char *input = malloc((size_t)MAX_INPUT_LENGTH + 2U);

    if (input == NULL) {
        fputs("Memory allocation error\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, MAX_INPUT_LENGTH + 2, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        puts("false");
        free(input);
        return EXIT_SUCCESS;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > (size_t)MAX_INPUT_LENGTH) {
        if (consume_line_remainder() < 0) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Input too long\n", stderr);
        }

        free(input);
        return EXIT_FAILURE;
    } else if (length == (size_t)MAX_INPUT_LENGTH) {
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

                free(input);
                return EXIT_FAILURE;
            }
        } else if (ferror(stdin)) {
            fputs("Input error\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }
    }

    puts(frequencies_are_valid(input) ? "true" : "false");

    free(input);
    return EXIT_SUCCESS;
}