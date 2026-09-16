#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_undulating(unsigned long long number)
{
    unsigned int first;
    unsigned int second;

    if (number < 100U) {
        return false;
    }

    first = (unsigned int)(number % 10U);
    number /= 10U;
    second = (unsigned int)(number % 10U);

    if (first == second) {
        return false;
    }

    number /= 10U;

    while (number > 0U) {
        unsigned int digit = (unsigned int)(number % 10U);

        if (digit != first) {
            return false;
        }

        first = second;
        second = digit;
        number /= 10U;
    }

    return true;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    unsigned long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
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