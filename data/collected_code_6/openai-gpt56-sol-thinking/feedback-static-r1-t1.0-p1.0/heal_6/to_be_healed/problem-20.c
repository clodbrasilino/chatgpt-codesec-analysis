#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

bool is_woodall(uint64_t value)
{
    uint64_t n = 1;
    uint64_t power = 2;

    for (;;) {
        uint64_t candidate;

        if (n > UINT64_MAX / power) {
            return false;
        }

        candidate = n * power - 1;

        if (candidate == value) {
            return true;
        }

        if (candidate > value || power > UINT64_MAX / 2) {
            return false;
        }

        ++n;
        power *= 2;
    }
}

static void discard_line(int ch)
{
    while (ch != '\n' && ch != EOF) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }
}

bool read_uint64(uint64_t *value)
{
    uint64_t result = 0;
    bool overflow = false;
    int ch;

    if (value == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = fgetc(stdin);

    if (ch == EOF) {
        return false;
    }

    while (ch != '\n' && isspace((unsigned char)ch)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return false;
        }
    }

    if (ch == '+') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } else if (ch == '-') {
        discard_line(ch);
        return false;
    }

    if (ch == EOF || ch == '\n' || !isdigit((unsigned char)ch)) {
        discard_line(ch);
        return false;
    }

    while (ch != EOF && isdigit((unsigned char)ch)) {
        uint64_t digit = (uint64_t)(ch - '0');

        if (result > (UINT64_MAX - digit) / 10) {
            overflow = true;
        } else if (!overflow) {
            result = result * 10 + digit;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    while (ch != EOF && ch != '\n' && isspace((unsigned char)ch)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch != EOF && ch != '\n') {
        discard_line(ch);
        return false;
    }

    if (ferror(stdin) || overflow) {
        return false;
    }

    *value = result;
    return true;
}

int main(void)
{
    uint64_t value;

    if (!read_uint64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (is_woodall(value)) {
        puts("Woodall number");
    } else {
        puts("Not a Woodall number");
    }

    return EXIT_SUCCESS;
}