#include <errno.h>
#include <stdint.h>
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
    enum { INPUT_SIZE = 256 };
    char input[INPUT_SIZE];
    char *end;
    unsigned long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs(ferror(stdin) ? "Failed to read input.\n" : "Invalid number.\n",
              stderr);
        return EXIT_FAILURE;
    }

    {
        size_t length = 0U;

        while (input[length] != '\0' && input[length] != '\n') {
            ++length;
        }

        if (input[length] == '\n') {
            input[length] = '\0';
        } else {
            int ch = fgetc(stdin);

            if (ch != '\n' && ch != EOF) {
                while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
                }

                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            if (ch == EOF && ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }
        }
    }

    errno = 0;
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