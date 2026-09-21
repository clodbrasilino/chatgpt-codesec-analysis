#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int octal_to_decimal(const char *octal, uintmax_t *decimal)
{
    char *end;
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
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fprintf(stderr, "Input is too long.\n");
        return EXIT_FAILURE;
    }

    if (!octal_to_decimal(input, &decimal)) {
        fprintf(stderr, "Invalid octal number.\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", decimal);
    return EXIT_SUCCESS;
}