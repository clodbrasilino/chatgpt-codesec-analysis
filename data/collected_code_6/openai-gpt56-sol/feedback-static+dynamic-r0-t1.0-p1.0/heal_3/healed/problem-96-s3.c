#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t count_divisors(uint64_t value)
{
    uint64_t count = 0;

    for (uint64_t divisor = 1; divisor <= value / divisor; ++divisor) {
        if (value % divisor == 0) {
            count += (divisor == value / divisor) ? UINT64_C(1) : UINT64_C(2);
        }
    }

    return count;
}

int main(void)
{
    char buffer[256];
    char *end;
    uintmax_t value;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    char *newline = buffer;
    while (*newline != '\0' && *newline != '\n') {
        ++newline;
    }

    if (*newline == '\n') {
        *newline = '\0';
    } else if (!feof(stdin)) {
        int character;

        do {
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || value == 0 || value > UINT64_MAX) {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", count_divisors((uint64_t)value));
    return EXIT_SUCCESS;
}