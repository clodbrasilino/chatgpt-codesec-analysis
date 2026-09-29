#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int parity(unsigned long long number)
{
    unsigned int result = 0U;

    while (number != 0ULL) {
        result ^= 1U;
        number &= number - 1ULL;
    }

    return result;
}

int main(void)
{
    char input[128];
    char *end;
    unsigned long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[0] != '\0' && input[sizeof input - 2U] != '\n') {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    end = NULL;
    number = strtoull(input, &end, 0);

    if (end == input || errno == ERANGE) {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid trailing characters.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%u\n", parity(number));
    return EXIT_SUCCESS;
}