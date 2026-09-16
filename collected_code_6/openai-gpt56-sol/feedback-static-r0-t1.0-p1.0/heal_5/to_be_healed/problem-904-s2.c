#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_even(int number)
{
    return number % 2 == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    const char *input;
    char *end = NULL;
    long value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    input = argv[1];
    errno = 0;
    value = strtol(input, &end, 10);

    if (errno == ERANGE ||
        end == input ||
        *end != '\0' ||
        value < INT_MIN ||
        value > INT_MAX) {
        fprintf(stderr, "Invalid integer\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", is_even((int)value) ? "true" : "false");
    return EXIT_SUCCESS;
}