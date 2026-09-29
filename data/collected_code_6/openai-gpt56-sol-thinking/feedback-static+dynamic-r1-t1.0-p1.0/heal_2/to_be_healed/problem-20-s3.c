#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_uint64(uint64_t *value)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF || ch == '-') {
        return false;
    }

    if (ch == '+') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF || !isdigit((unsigned char)ch)) {
        return false;
    }

    uint64_t result = 0;

    do {
        unsigned int digit = (unsigned int)(ch - '0');

        if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
            return false;
        }

        result = result * UINT64_C(10) + digit;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isdigit((unsigned char)ch));

    while (ch != EOF) {
        if (!isspace((unsigned char)ch)) {
            return false;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ferror(stdin)) {
        return false;
    }

    *value = result;
    return true;
}

static bool is_woodall(uint64_t number)
{
    for (uint64_t index = 1; index < 64; ++index) {
        if (index > (UINT64_MAX >> index)) {
            break;
        }

        uint64_t candidate = (index << index) - UINT64_C(1);

        if (candidate == number) {
            return true;
        }

        if (candidate > number) {
            break;
        }
    }

    return false;
}

int main(void)
{
    uint64_t value;

    if (!read_uint64(&value)) {
        return EXIT_FAILURE;
    }

    const char *result = is_woodall(value)
        ? "Woodall number\n"
        : "Not a Woodall number\n";

    if (fputs(result, stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}