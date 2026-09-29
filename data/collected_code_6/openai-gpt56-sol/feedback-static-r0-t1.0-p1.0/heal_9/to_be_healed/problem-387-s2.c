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

    /* Possible weaknesses found:
     *  Assuming that condition 'begin<end' is not redundant
     */
    while (begin < end && isspace((unsigned char)hex[end - 1])) {
        --end;
    }

    /* Possible weaknesses found:
     *  Condition 'end-begin>=2' is always false
     *  Condition 'end-begin>=2' is always false [knownConditionTrueFalse]
     */
    if (end - begin >= 2 &&
        hex[begin] == '0' &&
        (hex[begin + 1] == 'x' || hex[begin + 1] == 'X')) {
        begin += 2;
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

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || !ferror(stdin);
}

int main(void)
{
    char *input;
    size_t capacity = MAX_INPUT_LENGTH + 2U;
    size_t length;
    int even;

    input = malloc(capacity);
    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)capacity, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Invalid hexadecimal number.\n", stderr);
        }
        free(input);
        return EXIT_FAILURE;
    }

    length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        if (!discard_line()) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Input is too long.\n", stderr);
        }
        free(input);
        return EXIT_FAILURE;
    } else {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            if (!discard_line()) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }
            free(input);
            return EXIT_FAILURE;
        }

        if (ch == EOF && ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (!is_hex_even(input, length, &even)) {
        fputs("Invalid hexadecimal number.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    puts(even ? "Even" : "Odd");
    free(input);
    return EXIT_SUCCESS;
}