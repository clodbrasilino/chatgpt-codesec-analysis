#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static int octal_to_decimal(const char *octal, uintmax_t *decimal)
{
    char *end = NULL;
    uintmax_t value;

    if (octal == NULL || decimal == NULL || *octal == '\0' || *octal == '-') {
        return 0;
    }

    errno = 0;
    value = strtoumax(octal, &end, 8);

    if (errno == ERANGE || end == octal || *end != '\0') {
        return 0;
    }

    *decimal = value;
    return 1;
}

int main(void)
{
    char input[256];
    uintmax_t decimal;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    if (!octal_to_decimal(input, &decimal)) {
        fprintf(stderr, "Invalid octal number.\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", decimal);
    return EXIT_SUCCESS;
}