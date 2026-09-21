#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binary_to_decimal_stream(FILE *stream, uintmax_t *result)
{
    uintmax_t value = 0;
    int ch;
    int found_digit = 0;

    if (stream == NULL || result == NULL) {
        errno = EINVAL;
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        unsigned int digit;

        if (ch == '0') {
            digit = 0U;
        } else if (ch == '1') {
            digit = 1U;
        } else {
            errno = EINVAL;
            return -1;
        }

        found_digit = 1;

        if (value > (UINTMAX_MAX - digit) / UINTMAX_C(2)) {
            errno = ERANGE;
            return -1;
        }

        value = value * UINTMAX_C(2) + digit;
    }

    if (ferror(stream)) {
        return -1;
    }

    if (!found_digit) {
        errno = EINVAL;
        return -1;
    }

    *result = value;
    return 0;
}

int main(void)
{
    uintmax_t decimal;

    if (binary_to_decimal_stream(stdin, &decimal) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", decimal) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}