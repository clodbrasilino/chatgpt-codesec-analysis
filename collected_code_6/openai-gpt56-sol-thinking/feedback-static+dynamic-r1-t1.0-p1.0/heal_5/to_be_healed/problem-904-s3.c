#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_even(int number)
{
    return number % 2 == 0;
}

static bool parse_int(const char *text, int *result)
{
    char *end;
    long value;

    errno = 0;
    value = strtol(text, &end, 10);

    if (errno == ERANGE ||
        end == text ||
        *end != '\0' ||
        value < INT_MIN ||
        value > INT_MAX) {
        return false;
    }

    *result = (int)value;
    return true;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    int value;

    if (argc != 2 || !parse_int(argv[1], &value)) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", is_even(value) ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}