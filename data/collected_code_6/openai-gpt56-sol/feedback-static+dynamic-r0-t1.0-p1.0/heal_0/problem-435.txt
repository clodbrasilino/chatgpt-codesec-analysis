#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int last_digit(long long number)
{
    return (int)(llabs(number % 10));
}

int main(void)
{
    char input[128];
    char *end;
    long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoll(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return EXIT_FAILURE;
    }

    printf("%d\n", last_digit(number));
    return EXIT_SUCCESS;
}