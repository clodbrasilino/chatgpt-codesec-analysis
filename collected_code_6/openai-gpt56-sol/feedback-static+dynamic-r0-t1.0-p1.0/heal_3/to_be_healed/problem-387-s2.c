#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int is_hex_even(const char *hex, int *is_even)
{
    const unsigned char *p;
    unsigned char last_digit = 0;
    int has_digit = 0;

    if (hex == NULL || is_even == NULL) {
        return 0;
    }

    p = (const unsigned char *)hex;

    while (isspace(*p)) {
        ++p;
    }

    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
        p += 2;
    }

    while (isxdigit(*p)) {
        last_digit = *p++;
        has_digit = 1;
    }

    if (!has_digit) {
        return 0;
    }

    while (isspace(*p)) {
        ++p;
    }

    if (*p != '\0') {
        return 0;
    }

    *is_even = last_digit == '0' || last_digit == '2' ||
               last_digit == '4' || last_digit == '6' ||
               last_digit == '8' || last_digit == 'a' ||
               last_digit == 'A' || last_digit == 'c' ||
               last_digit == 'C' || last_digit == 'e' ||
               last_digit == 'E';

    return 1;
}

int main(void)
{
    enum { INPUT_SIZE = 4096 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    int even;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Invalid hexadecimal number.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    for (size_t i = 0; input[i] != '\0'; ++i) {
        if (input[i] == '\n') {
            input[i] = '\0';
            break;
        }
    }

    if (input[0] != '\0') {
        size_t length = 0;

        while (input[length] != '\0') {
            ++length;
        }

        if (length == sizeof(input) - 1 && input[length - 1] != '\n') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
            if (ch != '\n' && ch != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                while ((ch = getchar()) != '\n' && ch != EOF) {
                }
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            if (ch == EOF && ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }
        }
    }

    if (!is_hex_even(input, &even)) {
        fputs("Invalid hexadecimal number.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(even ? "Even" : "Odd");
    return EXIT_SUCCESS;
}