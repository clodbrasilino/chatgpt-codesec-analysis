#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int last_two_digits_of_factorial(unsigned long long n)
{
    if (n >= 10ULL) {
        return 0U;
    }

    unsigned int result = 1U;

    for (unsigned long long i = 2ULL; i <= n; ++i) {
        result = (result * (unsigned int)i) % 100U;
    }

    return result;
}

int main(void)
{
    char input[128];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = 0U;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input || input[length] != '\n') {
        int ch;
        int extra_input = 0;

        while ((ch = getchar()) != '\n' && ch != EOF) {
            extra_input = 1;
        }

        if (length == sizeof input || extra_input) {
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    char *end = NULL;
    unsigned long long n = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input || input[0] == '-') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%02u\n", last_two_digits_of_factorial(n));
    return EXIT_SUCCESS;
}