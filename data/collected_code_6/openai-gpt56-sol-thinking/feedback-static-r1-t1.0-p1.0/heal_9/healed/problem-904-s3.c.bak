#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_even(int number)
{
    return number % 2 == 0;
}

int main(int argc, char *argv[const])
{
    const char *argument;
    char *end;
    long value;

    if (argc != 2) {
        return EXIT_FAILURE;
    }

    argument = argv[1];
    errno = 0;
    value = strtol(argument, &end, 10);

    if (errno == ERANGE ||
        end == argument ||
        *end != '\0' ||
        value < INT_MIN ||
        value > INT_MAX) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", is_even((int)value) ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}