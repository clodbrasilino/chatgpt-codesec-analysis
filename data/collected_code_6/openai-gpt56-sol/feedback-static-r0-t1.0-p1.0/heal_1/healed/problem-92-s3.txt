#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_undulating(unsigned long long number)
{
    unsigned int first;
    unsigned int second;

    if (number < 100ULL) {
        return false;
    }

    first = (unsigned int)(number % 10ULL);
    number /= 10ULL;
    second = (unsigned int)(number % 10ULL);

    if (first == second) {
        return false;
    }

    number /= 10ULL;

    while (number != 0ULL) {
        unsigned int digit = (unsigned int)(number % 10ULL);

        if (digit != first) {
            return false;
        }

        first = second;
        second = digit;
        number /= 10ULL;
    }

    return true;
}

int main(void)
{
    char input[128];
    char *end;
    unsigned long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (input[0] != '\0') {
        size_t length = 0;

        while (length < sizeof input && input[length] != '\0' &&
               input[length] != '\n') {
            ++length;
        }

        if (length == sizeof input) {
            return EXIT_FAILURE;
        }

        if (input[length] != '\n' && !feof(stdin)) {
            int ch = getchar();

            if (ch != '\n' && ch != EOF) {
                while ((ch = getchar()) != '\n' && ch != EOF) {
                }
                return EXIT_FAILURE;
            }
        }
    }

    errno = 0;
    end = NULL;
    number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    printf("%s\n", is_undulating(number) ? "Undulating" : "Not undulating");

    return EXIT_SUCCESS;
}