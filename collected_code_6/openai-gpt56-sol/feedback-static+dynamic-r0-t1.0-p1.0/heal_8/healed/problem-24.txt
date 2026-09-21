#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINTMAX_BINARY_DIGITS (sizeof(uintmax_t) * 8U)
#define BINARY_BUFFER_SIZE (UINTMAX_BINARY_DIGITS + 2U)

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
    size_t length;
    int ch;

    if (buffer == NULL || capacity < BINARY_BUFFER_SIZE) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return -1;
    }

    length = 0U;
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

    ch = fgetc(stdin);
    if (ch == '\n' || ch == EOF) {
        if (ch == EOF && ferror(stdin)) {
            return -1;
        }
        return 0;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return -1;
}

int main(void)
{
    char binary[BINARY_BUFFER_SIZE];
    uintmax_t decimal;

    if (read_binary_line(binary, sizeof(binary)) != 0) {
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