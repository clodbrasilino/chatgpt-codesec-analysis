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

bool read_uint64(uint64_t *value)
{
    uint64_t result = 0;
    int current;

    if (value == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    current = fgetc(stdin);

    while (current != EOF && current != '\n' &&
           isspace((unsigned char)current)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        current = fgetc(stdin);
    }

    if (current == EOF || current == '\n' || current == '-') {
        return false;
    }

    if (current == '+') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        current = fgetc(stdin);
    }

    if (current == EOF || !isdigit((unsigned char)current)) {
        return false;
    }

    while (current != EOF && isdigit((unsigned char)current)) {
        uint64_t digit = (uint64_t)(current - '0');

        if (result > (UINT64_MAX - digit) / 10) {
            return false;
        }

        result = result * 10 + digit;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        current = fgetc(stdin);
    }

    while (current != EOF && current != '\n' &&
           isspace((unsigned char)current)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        current = fgetc(stdin);
    }

    if (current == EOF) {
        if (ferror(stdin)) {
            return false;
        }
    } else if (current != '\n') {
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