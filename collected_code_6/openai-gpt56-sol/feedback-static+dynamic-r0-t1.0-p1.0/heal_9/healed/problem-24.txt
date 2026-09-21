#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINTMAX_BINARY_DIGITS (sizeof(uintmax_t) * 8U)
#define BINARY_BUFFER_SIZE (UINTMAX_BINARY_DIGITS + 2U)

static int discard_line(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return (ch == EOF && ferror(stdin)) ? -1 : 0;
}

static int read_binary_line(char *buffer, size_t capacity)
{
    size_t length = 0U;
    int ch;

    if (buffer == NULL || capacity < 2U) {
        return -1;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch != '0' && ch != '1') {
            if (discard_line() != 0) {
                return -1;
            }
            return -1;
        }

        if (length + 1U >= capacity) {
            if (discard_line() != 0) {
                return -1;
            }
            return -1;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    if (length == 0U) {
        return -1;
    }

    buffer[length] = '\0';
    return 0;
}

static int binary_to_decimal(const char *binary, uintmax_t *decimal)
{
    uintmax_t value = 0U;

    if (binary == NULL || decimal == NULL || *binary == '\0') {
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

        if (value > (UINTMAX_MAX - digit) / 2U) {
            return -1;
        }

        value = value * 2U + digit;
    }

    *decimal = value;
    return 0;
}

int main(void)
{
    char *binary;
    uintmax_t decimal;
    int result = EXIT_FAILURE;

    binary = malloc(BINARY_BUFFER_SIZE);
    if (binary == NULL) {
        return EXIT_FAILURE;
    }

    if (read_binary_line(binary, BINARY_BUFFER_SIZE) == 0 &&
        binary_to_decimal(binary, &decimal) == 0 &&
        printf("%" PRIuMAX "\n", decimal) >= 0) {
        result = EXIT_SUCCESS;
    }

    free(binary);
    return result;
}