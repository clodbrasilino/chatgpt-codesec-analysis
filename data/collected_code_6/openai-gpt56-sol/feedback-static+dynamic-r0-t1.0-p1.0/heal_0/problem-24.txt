#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binary_to_decimal(const char *binary, uintmax_t *decimal)
{
    char *end = NULL;
    uintmax_t value;

    if (binary == NULL || decimal == NULL || *binary == '\0') {
        return -1;
    }

    errno = 0;
    value = strtoumax(binary, &end, 2);

    if (errno == ERANGE || end == binary || *end != '\0') {
        return -1;
    }

    *decimal = value;
    return 0;
}

int main(void)
{
    char binary[256];
    uintmax_t decimal;

    if (fgets(binary, sizeof binary, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (binary[length] != '\0' && binary[length] != '\n') {
        ++length;
    }

    if (binary[length] == '\n') {
        binary[length] = '\0';
    } else if (binary[length] != '\0') {
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