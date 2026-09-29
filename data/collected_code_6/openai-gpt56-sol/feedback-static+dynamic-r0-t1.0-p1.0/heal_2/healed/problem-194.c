#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static int octal_to_decimal(const char *octal, uintmax_t *decimal)
{
    char *end = NULL;
    uintmax_t value;

    if (octal == NULL || decimal == NULL || *octal == '\0' || *octal == '-') {
        return -1;
    }

    errno = 0;
    value = strtoumax(octal, &end, 8);

    if (errno == ERANGE || end == octal || *end != '\0') {
        return -1;
    }

    *decimal = value;
    return 0;
}

int main(int argc, const char *const argv[])
{
    uintmax_t decimal;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <octal-number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (octal_to_decimal(argv[1], &decimal) != 0) {
        fprintf(stderr, "Invalid or out-of-range octal number\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", decimal);
    return EXIT_SUCCESS;
}