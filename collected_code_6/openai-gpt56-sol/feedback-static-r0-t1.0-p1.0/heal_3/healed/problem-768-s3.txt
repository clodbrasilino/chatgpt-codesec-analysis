#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <stdint.h>

static int has_odd_parity(unsigned long long value)
{
    int parity = 0;

    while (value != 0ULL) {
        parity ^= 1;
        value &= value - 1ULL;
    }

    return parity;
}

int main(void)
{
    enum { INPUT_SIZE = 256 };
    char input[INPUT_SIZE];
    char *end;
    unsigned long long value;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    end = input;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end == '\n') {
        *end = '\0';
    } else if (*end == '\0' && !feof(stdin)) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoull(input, &end, 0);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", has_odd_parity(value) ? "Odd parity" : "Even parity") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}