#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int is_even(long number)
{
    return (number & 1L) == 0L;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtol(input, &end, 10);

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

    printf("%s\n", is_even(number) ? "Even" : "Odd");

    return EXIT_SUCCESS;
}