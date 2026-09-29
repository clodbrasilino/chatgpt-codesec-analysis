#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <stdint.h>

static int find_remainder(int dividend, int divisor, int *remainder)
{
    if (remainder == NULL || divisor == 0) {
        return 0;
    }

    if (dividend == INT_MIN && divisor == -1) {
        *remainder = 0;
        return 1;
    }

    *remainder = dividend % divisor;
    return 1;
}

static int read_int(const char *prompt, int *value)
{
    char buffer[256];
    char *end;
    long parsed;
    size_t length;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (buffer[length] == '\0' && !feof(stdin)) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtol(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

int main(void)
{
    int dividend;
    int divisor;
    int remainder;

    if (!read_int("Enter the dividend: ", &dividend) ||
        !read_int("Enter the divisor: ", &divisor)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_remainder(dividend, divisor, &remainder)) {
        fputs("The divisor must not be zero.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Remainder: %d\n", remainder) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}