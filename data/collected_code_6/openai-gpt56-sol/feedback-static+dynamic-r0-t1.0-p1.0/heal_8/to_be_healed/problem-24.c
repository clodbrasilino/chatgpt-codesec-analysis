#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINTMAX_BINARY_DIGITS (sizeof(uintmax_t) * 8U)
#define BINARY_BUFFER_SIZE (UINTMAX_BINARY_DIGITS + 2U)

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return (ch == EOF && ferror(stdin)) ? -1 : 0;
}

static int binary_to_decimal(const char *binary, uintmax_t *decimal)
{
    uintmax_t value = 0;

    if (binary == NULL || decimal == NULL || binary[0] == '\0') {
        return -1;
    }

    for (const char *p = binary; *p != '\0'; ++p) {
        unsigned int digit;

        if (*p == '0') {
            digit = 0U;
        } else if (*p == '1') {
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
    size_t length = 0;
    int ch;
    int overflow = 0;
    int invalid = 0;

    if (buffer == NULL || capacity < BINARY_BUFFER_SIZE) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (ch != '0' && ch != '1') {
            invalid = 1;
        } else if (length < UINTMAX_BINARY_DIGITS) {
            buffer[length++] = (char)ch;
        } else {
            overflow = 1;
        }
    }

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    if (length == 0U || invalid || overflow) {
        return -1;
    }

    buffer[length] = '\0';
    return 0;
}

int main(void)
{
    char *binary;
    uintmax_t decimal;
    int status = EXIT_FAILURE;

    binary = malloc(BINARY_BUFFER_SIZE);
    if (binary == NULL) {
        return EXIT_FAILURE;
    }

    if (read_binary_line(binary, BINARY_BUFFER_SIZE) == 0 &&
        binary_to_decimal(binary, &decimal) == 0 &&
        printf("%" PRIuMAX "\n", decimal) >= 0) {
        status = EXIT_SUCCESS;
    }

    free(binary);
    return status;
}