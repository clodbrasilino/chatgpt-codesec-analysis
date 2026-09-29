#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int octal_to_decimal(const char *input, uintmax_t *result)
{
    char *end;
    uintmax_t value;

    if (input == NULL || result == NULL || *input == '\0') {
        return -1;
    }

    errno = 0;
    value = strtoumax(input, &end, 8);

    if (errno == ERANGE || end == input || *end != '\0') {
        return -1;
    }

    *result = value;
    return 0;
}

int main(void)
{
    char input[256];
    uintmax_t decimal;
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    length = strcspn(input, "\r\n");

    if (input[length] != '\0') {
        input[length] = '\0';
    } else if (length == sizeof input - 1) {
        int ch;

        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            fputs("Input too long\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (octal_to_decimal(input, &decimal) != 0) {
        fputs("Invalid octal number\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", decimal) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}