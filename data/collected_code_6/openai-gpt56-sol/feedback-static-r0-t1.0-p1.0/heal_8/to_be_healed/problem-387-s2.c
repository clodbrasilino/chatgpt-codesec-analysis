#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_INPUT_LENGTH = 4096 };

static int is_hex_even(const char *hex, size_t length, int *is_even)
{
    size_t begin = 0;
    size_t end = length;
    unsigned char last;

    if (hex == NULL || is_even == NULL || length == 0) {
        return 0;
    }

    while (begin < end && isspace((unsigned char)hex[begin])) {
        ++begin;
    }

    while (begin < end && isspace((unsigned char)hex[end - 1])) {
        --end;
    }

    if (begin < end && hex[begin] == '0') {
        size_t remaining = end - begin;

        if (remaining >= 2 &&
            (hex[begin + 1] == 'x' || hex[begin + 1] == 'X')) {
            begin += 2;
        }
    }

    if (begin == end) {
        return 0;
    }

    for (size_t i = begin; i < end; ++i) {
        if (!isxdigit((unsigned char)hex[i])) {
            return 0;
        }
    }

    last = (unsigned char)tolower((unsigned char)hex[end - 1]);
    *is_even = last == '0' || last == '2' || last == '4' ||
               last == '6' || last == '8' || last == 'a' ||
               last == 'c' || last == 'e';

    return 1;
}

static int consume_line_tail(int *line_ended)
{
    int ch;

    if (line_ended == NULL) {
        return 0;
    }

    *line_ended = 0;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    if (ch == '\n') {
        *line_ended = 1;
        return 1;
    }

    return ferror(stdin) == 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LENGTH + 2];
    size_t length;
    int even;

    if (fgets(input, (int)sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Invalid hexadecimal number.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        int line_ended;

        if (!consume_line_tail(&line_ended)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Input is too long.\n", stderr);
        }
        return EXIT_FAILURE;
    } else {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n') {
        } else if (ch == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }
        } else {
            int line_ended;

            if (!consume_line_tail(&line_ended)) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }
            return EXIT_FAILURE;
        }
    }

    if (!is_hex_even(input, length, &even)) {
        fputs("Invalid hexadecimal number.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(even ? "Even" : "Odd");
    return EXIT_SUCCESS;
}