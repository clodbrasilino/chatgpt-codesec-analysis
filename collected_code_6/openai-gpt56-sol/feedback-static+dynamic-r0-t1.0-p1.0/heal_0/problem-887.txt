#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int is_odd(long long number)
{
    return (number & 1LL) != 0;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoll(input, &end, 10);

    if (end == input || errno == ERANGE) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", is_odd(number) ? "Odd" : "Not odd") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}