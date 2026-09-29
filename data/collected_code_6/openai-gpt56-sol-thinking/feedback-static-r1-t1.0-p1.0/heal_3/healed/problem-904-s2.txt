#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static bool is_even(int number)
{
    return number % 2 == 0;
}

int main(int argc, char **const argv)
{
    const char *const input = argc == 2 ? argv[1] : NULL;
    char *end = NULL;
    long value;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(input, &end, 10);

    if (errno == ERANGE ||
        end == input ||
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