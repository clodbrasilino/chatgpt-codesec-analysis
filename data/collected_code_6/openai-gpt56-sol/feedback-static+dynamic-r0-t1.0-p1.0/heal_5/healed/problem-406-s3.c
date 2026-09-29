#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int parity(unsigned long long value)
{
    unsigned int result = 0U;

    while (value != 0ULL) {
        result ^= 1U;
        value &= value - 1ULL;
    }

    return result;
}

int main(void)
{
    char input[256];
    char *end;
    unsigned long long value;
    int character;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    end = input;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end == '\n') {
        *end = '\0';
    } else if (*end != '\0') {
        return EXIT_FAILURE;
    } else {
        character = fgetc(stdin);
        if (character != '\n' && character != EOF) {
            while (character != '\n' && character != EOF) {
                character = fgetc(stdin);
            }
            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    end = NULL;
    value = strtoull(input, &end, 0);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (printf("%u\n", parity(value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}