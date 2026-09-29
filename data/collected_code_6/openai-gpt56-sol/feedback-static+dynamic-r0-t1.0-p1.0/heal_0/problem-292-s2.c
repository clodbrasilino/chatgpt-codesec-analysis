#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int find_quotient(int dividend, int divisor, int *quotient)
{
    if (quotient == NULL || divisor == 0) {
        return -1;
    }

    if (dividend == INT_MIN && divisor == -1) {
        return -1;
    }

    *quotient = dividend / divisor;
    return 0;
}

static int parse_int(const char *text, int *value)
{
    char *end = NULL;
    long parsed;

    if (text == NULL || value == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return -1;
    }

    *value = (int)parsed;
    return 0;
}

int main(int argc, char *argv[])
{
    int dividend;
    int divisor;
    int quotient;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <dividend> <divisor>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_int(argv[1], &dividend) != 0 ||
        parse_int(argv[2], &divisor) != 0) {
        fputs("Error: arguments must be valid integers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_quotient(dividend, divisor, &quotient) != 0) {
        fputs("Error: division by zero or integer overflow.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", quotient) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}