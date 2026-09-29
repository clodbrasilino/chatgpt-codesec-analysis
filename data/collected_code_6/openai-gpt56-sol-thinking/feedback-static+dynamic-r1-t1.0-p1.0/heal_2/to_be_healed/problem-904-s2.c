#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static bool is_even(int number)
{
    return number % 2 == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end = NULL;
    long value;

    if (argc != 2) {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        value < INT_MIN || value > INT_MAX) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", is_even((int)value) ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}