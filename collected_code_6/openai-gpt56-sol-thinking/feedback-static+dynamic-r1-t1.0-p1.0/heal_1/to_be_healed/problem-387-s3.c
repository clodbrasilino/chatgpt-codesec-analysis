#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    HEX_INVALID = -1,
    HEX_ODD = 0,
    HEX_EVEN = 1
} HexParity;

static int hex_digit_value(unsigned char character)
{
    if (character >= '0' && character <= '9') {
        return character - '0';
    }

    if (character >= 'a' && character <= 'f') {
        return character - 'a' + 10;
    }

    if (character >= 'A' && character <= 'F') {
        return character - 'A' + 10;
    }

    return -1;
}

static HexParity check_hex_parity(const char *text)
{
    const unsigned char *current;
    int last_digit = -1;

    if (text == NULL) {
        return HEX_INVALID;
    }

    current = (const unsigned char *)text;

    while (isspace(*current) != 0) {
        ++current;
    }

    if (*current == '+' || *current == '-') {
        ++current;
    }

    if (current[0] == '0' && (current[1] == 'x' || current[1] == 'X')) {
        current += 2;
    }

    while (hex_digit_value(*current) >= 0) {
        last_digit = hex_digit_value(*current);
        ++current;
    }

    if (last_digit < 0) {
        return HEX_INVALID;
    }

    while (isspace(*current) != 0) {
        ++current;
    }

    if (*current != '\0') {
        return HEX_INVALID;
    }

    return (last_digit % 2 == 0) ? HEX_EVEN : HEX_ODD;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[4096];
    HexParity parity;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin) != 0) {
            fputs("Input error\n", stderr);
        } else {
            fputs("No input provided\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            if (ferror(stdin) != 0) {
                fputs("Input error\n", stderr);
            } else {
                fputs("Input is too long\n", stderr);
            }
            return EXIT_FAILURE;
        }

        if (ferror(stdin) != 0) {
            fputs("Input error\n", stderr);
            return EXIT_FAILURE;
        }
    }

    parity = check_hex_parity(input);

    if (parity == HEX_INVALID) {
        fputs("Invalid hexadecimal number\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(parity == HEX_EVEN ? "Even" : "Odd") == EOF) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}