#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BINARY_BUFFER_SIZE ((sizeof(uintmax_t) * 8U) + 2U)

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
    char binary[BINARY_BUFFER_SIZE];
    uintmax_t decimal;
    size_t length = 0;

    if (fgets(binary, sizeof binary, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    while (binary[length] != '\0' && binary[length] != '\n') {
        ++length;
    }

    if (binary[length] == '\n') {
        binary[length] = '\0';
    } else {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
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