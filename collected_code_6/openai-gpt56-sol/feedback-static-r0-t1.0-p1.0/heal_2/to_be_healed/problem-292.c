#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int divide_numbers(int dividend, int divisor, int *quotient)
{
    if (quotient == NULL || divisor == 0) {
        return 0;
    }

    if (dividend == INT_MIN && divisor == -1) {
        return 0;
    }

    *quotient = dividend / divisor;
    return 1;
}

static int parse_int(const char *text, int *value)
{
    char *end = NULL;
    long parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    int dividend;
    int divisor;
    int quotient;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <dividend> <divisor>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_int(argv[1], &dividend) || !parse_int(argv[2], &divisor)) {
        fprintf(stderr, "Error: both arguments must be valid integers.\n");
        return EXIT_FAILURE;
    }

    if (!divide_numbers(dividend, divisor, &quotient)) {
        fprintf(stderr, "Error: division by zero or integer overflow.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", quotient);
    return EXIT_SUCCESS;
}