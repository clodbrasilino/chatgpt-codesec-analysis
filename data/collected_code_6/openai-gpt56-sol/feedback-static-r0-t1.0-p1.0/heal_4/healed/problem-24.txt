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
    char *binary = NULL;
    size_t length = 0;
    size_t capacity = 0;
    uintmax_t decimal;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (ch != '0' && ch != '1') {
            free(binary);
            return EXIT_FAILURE;
        }

        if (length == SIZE_MAX - 1) {
            free(binary);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_binary;

            if (capacity == 0) {
                new_capacity = 32;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(binary);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                free(binary);
                return EXIT_FAILURE;
            }

            new_binary = realloc(binary, new_capacity);
            if (new_binary == NULL) {
                free(binary);
                return EXIT_FAILURE;
            }

            binary = new_binary;
            capacity = new_capacity;
        }

        binary[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(binary);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        free(binary);
        return EXIT_FAILURE;
    }

    binary[length] = '\0';

    if (binary_to_decimal(binary, &decimal) != 0) {
        free(binary);
        return EXIT_FAILURE;
    }

    free(binary);

    if (printf("%" PRIuMAX "\n", decimal) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}