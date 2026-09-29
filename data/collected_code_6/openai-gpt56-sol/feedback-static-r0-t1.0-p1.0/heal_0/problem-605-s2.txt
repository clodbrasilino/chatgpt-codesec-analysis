#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_prime(int value)
{
    if (value < 2) {
        return false;
    }

    if (value == 2) {
        return true;
    }

    if (value % 2 == 0) {
        return false;
    }

    for (int divisor = 3; divisor <= value / divisor; divisor += 2) {
        if (value % divisor == 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char input[128];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    const long parsed = strtol(input, &end, 10);

    if (end == input || errno == ERANGE || parsed < INT_MIN || parsed > INT_MAX) {
        fputs("Invalid integer.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid integer.\n", stderr);
        return EXIT_FAILURE;
    }

    const int value = (int)parsed;
    puts(is_prime(value) ? "Prime" : "Not prime");

    return EXIT_SUCCESS;
}