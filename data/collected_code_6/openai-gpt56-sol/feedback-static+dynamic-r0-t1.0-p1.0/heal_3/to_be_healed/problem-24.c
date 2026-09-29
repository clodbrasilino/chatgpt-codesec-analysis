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
            return -1;
        }

        value = value * 2 + digit;
    }

    *decimal = value;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     *  'UINTMAX_WIDTH' undeclared (first use in this function); did you mean 'UINTMAX_C'?
     *  use of undeclared identifier 'UINTMAX_WIDTH'
     */
    char binary[UINTMAX_WIDTH + 2];
    uintmax_t decimal;
    size_t length;
    int ch;

    if (fgets(binary, sizeof binary, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    for (length = 0; binary[length] != '\0' && binary[length] != '\n'; ++length) {
    }

    if (binary[length] == '\n') {
        binary[length] = '\0';
    } else if (binary[length] == '\0') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    if (binary_to_decimal(binary, &decimal) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", decimal) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}