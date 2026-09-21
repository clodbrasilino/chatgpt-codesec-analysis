#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_even(int number)
{
    return number % 2 == 0;
}

int main(int argc, char ** const argv)
{
    const char *argument;
    char *end = NULL;
    long value;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
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

    if (puts(is_even((int)value) ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}