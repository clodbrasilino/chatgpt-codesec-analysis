#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_even(int number)
{
    return number % 2 == 0;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
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