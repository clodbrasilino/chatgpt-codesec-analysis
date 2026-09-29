#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BINARY_BUFFER_SIZE (sizeof(uintmax_t) * 8U + 2U)

static int binary_to_decimal(const char *binary, uintmax_t *decimal)
{
    uintmax_t value = 0;

    if (binary == NULL || decimal == NULL || *binary == '\0') {
        return -1;
    }

    for (const unsigned char *p = (const unsigned char *)binary; *p != '\0'; ++p) {
        unsigned int digit;

        if (*p == (unsigned char)'0') {
            digit = 0U;
        } else if (*p == (unsigned char)'1') {
            digit = 1U;
        } else {
            return -1;
        }

        if (value > (UINTMAX_MAX - digit) / 2U) {
            return -1;
        }

        value = value * 2U + digit;
    }

    *decimal = value;
    return 0;
}

static int read_binary_line(char *buffer, size_t capacity)
{
    size_t length;

    if (buffer == NULL || capacity < 2U) {
        return -1;
    }

    if (fgets(buffer, capacity, stdin) == NULL) {
        return -1;
    }

    for (length = 0U; length < capacity && buffer[length] != '\0'; ++length) {
        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            return length == 0U ? -1 : 0;
        }
    }

    if (length == capacity) {
        return -1;
    }

    if (feof(stdin)) {
        return length == 0U ? -1 : 0;
    }

    {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n') {
            return length == 0U ? -1 : 0;
        }

        if (ch != EOF) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);
        }

        return -1;
    }
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