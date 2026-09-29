#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binary_to_decimal(const char *binary, uintmax_t *decimal)
{
    uintmax_t value = 0;

    if (binary == NULL || decimal == NULL || *binary == '\0') {
        return -1;
    }

    for (const unsigned char *p = (const unsigned char *)binary; *p != '\0'; ++p) {
        unsigned int digit;

        if (*p == '0') {
            digit = 0;
        } else if (*p == '1') {
            digit = 1;
        } else {
            return -1;
        }

        if (value > (UINTMAX_MAX - digit) / 2) {
            errno = ERANGE;
            return -1;
        }

        value = value * 2 + digit;
    }

    *decimal = value;
    return 0;
}

int main(void)
{
    enum { MAX_BINARY_DIGITS = sizeof(uintmax_t) * 8 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[MAX_BINARY_DIGITS + 1];
    size_t length = 0;
    uintmax_t decimal;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch != '0' && ch != '1') {
            return EXIT_FAILURE;
        }

        if (length >= MAX_BINARY_DIGITS) {
            return EXIT_FAILURE;
        }

        binary[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        return EXIT_FAILURE;
    }

    binary[length] = '\0';

    if (binary_to_decimal(binary, &decimal) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", decimal) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}