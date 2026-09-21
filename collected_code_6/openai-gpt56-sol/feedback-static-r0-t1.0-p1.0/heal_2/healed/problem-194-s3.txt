#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

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
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    uintmax_t decimal;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[--length] = '\0';
    }

    if (!octal_to_decimal(input, &decimal)) {
        free(input);
        fprintf(stderr, "Invalid octal number.\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", decimal);
    free(input);
    return EXIT_SUCCESS;
}