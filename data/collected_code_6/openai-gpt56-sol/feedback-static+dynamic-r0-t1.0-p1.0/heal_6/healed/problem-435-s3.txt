#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t last_digit(intmax_t number)
{
    uintmax_t magnitude;

    if (number < 0) {
        magnitude = (uintmax_t)(-(number + 1)) + UINTMAX_C(1);
    } else {
        magnitude = (uintmax_t)number;
    }

    return magnitude % UINTMAX_C(10);
}

int main(void)
{
    enum { INPUT_SIZE = 256 };
    char input[INPUT_SIZE];
    char *start;
    char *end;
    intmax_t number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int character;

        do {
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    number = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", last_digit(number)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}