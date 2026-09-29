#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINTMAX_BINARY_DIGITS (sizeof(uintmax_t) * 8U)
#define BINARY_BUFFER_SIZE (UINTMAX_BINARY_DIGITS + 2U)

static int read_binary_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2U) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return -1;
    }

    size_t length = 0U;

    while (buffer[length] != '\0' && buffer[length] != '\n') {
        if (buffer[length] != '0' && buffer[length] != '1') {
            return -1;
        }
        ++length;
    }

    if (length == 0U) {
        return -1;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int ch = fgetc(stdin);

    if (ch == '\n' || ch == EOF) {
        return (ch == EOF && ferror(stdin)) ? -1 : 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return -1;
}

static int binary_to_decimal(const char *binary, uintmax_t *decimal)
{
    uintmax_t value = 0U;

    if (binary == NULL || decimal == NULL || binary[0] == '\0') {
        return -1;
    }

    for (const char *p = binary; *p != '\0'; ++p) {
        uintmax_t digit;

        if (*p == '0') {
            digit = 0U;
        } else if (*p == '1') {
            digit = 1U;
        } else {
            return -1;
        }

        if (value > (UINTMAX_MAX - digit) / UINTMAX_C(2)) {
            return -1;
        }

        value = value * UINTMAX_C(2) + digit;
    }

    *decimal = value;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[BINARY_BUFFER_SIZE];
    uintmax_t decimal;

    if (read_binary_line(binary, sizeof binary) != 0) {
        return EXIT_FAILURE;
    }

    if (binary_to_decimal(binary, &decimal) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", decimal) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}