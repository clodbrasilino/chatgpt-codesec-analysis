#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

static bool is_even(int number)
{
    return number % 2 == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    long value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(argv[1], &end, 10);

    if (end == argv[1] || *end != '\0' || errno == ERANGE ||
        value < INT_MIN || value > INT_MAX) {
        fprintf(stderr, "Invalid integer\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", is_even((int)value) ? "true" : "false");
    return EXIT_SUCCESS;
}