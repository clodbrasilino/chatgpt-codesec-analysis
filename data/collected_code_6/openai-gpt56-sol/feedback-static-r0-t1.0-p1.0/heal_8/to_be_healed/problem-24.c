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
    uintmax_t decimal = 0;
    uintmax_t value = 0;
    size_t digits = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        unsigned int digit;

        if (ch == '0') {
            digit = 0;
        } else if (ch == '1') {
            digit = 1;
        } else {
            return EXIT_FAILURE;
        }

        if (value > (UINTMAX_MAX - digit) / 2) {
            errno = ERANGE;
            return EXIT_FAILURE;
        }

        value = value * 2 + digit;
        ++digits;
    }

    if (ferror(stdin) || digits == 0) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[sizeof(uintmax_t) * 8 + 1];
    size_t length = 0;
    uintmax_t temporary = value;

    do {
        binary[length++] = (char)('0' + (temporary & UINTMAX_C(1)));
        temporary >>= 1;
    } while (temporary != 0);

    for (size_t i = 0; i < length / 2; ++i) {
        char tmp = binary[i];
        binary[i] = binary[length - i - 1];
        binary[length - i - 1] = tmp;
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