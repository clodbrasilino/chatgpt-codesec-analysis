#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binary_to_decimal(const char *binary, uintmax_t *decimal)
{
    uintmax_t value = 0;

    if (binary == NULL || decimal == NULL || *binary == '\0') {
        errno = EINVAL;
        return -1;
    }

    for (const unsigned char *p = (const unsigned char *)binary;
         *p != '\0';
         ++p) {
        unsigned int digit;

        if (*p == '0') {
            digit = 0;
        } else if (*p == '1') {
            digit = 1;
        } else {
            errno = EINVAL;
            return -1;
        }

        if (value > (UINTMAX_MAX - digit) / UINTMAX_C(2)) {
            errno = ERANGE;
            return -1;
        }

        value = value * UINTMAX_C(2) + digit;
    }

    *decimal = value;
    return 0;
}

int main(void)
{
    char binary[sizeof(uintmax_t) * CHAR_BIT + 1];
    size_t length = 0;
    int ch;
    uintmax_t decimal;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (ch != '0' && ch != '1') {
            return EXIT_FAILURE;
        }

        if (length >= sizeof(binary) - 1) {
            errno = ERANGE;
            return EXIT_FAILURE;
        }

        binary[length++] = (char)ch;
    }

    if (ferror(stdin) || length == 0) {
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