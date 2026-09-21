#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool extract_maximum(const char *input, unsigned long long *maximum)
{
    const char *cursor;
    unsigned long long max_value = 0;
    bool found = false;

    if (input == NULL || maximum == NULL) {
        return false;
    }

    cursor = input;

    while (*cursor != '\0') {
        char *end;
        unsigned long long value;

        if (*cursor < '0' || *cursor > '9') {
            ++cursor;
            continue;
        }

        errno = 0;
        value = strtoull(cursor, &end, 10);

        if (end == cursor) {
            ++cursor;
            continue;
        }

        if (errno == ERANGE) {
            fprintf(stderr, "Numeric value is out of range\n");
            return false;
        }

        if (!found || value > max_value) {
            max_value = value;
            found = true;
        }

        cursor = end;
    }

    if (found) {
        *maximum = max_value;
    }

    return found;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    unsigned long long maximum;

    if (argc != 2) {
        fprintf(stderr,
                "Usage: %s \"text containing numbers\"\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    if (!extract_maximum(argv[1], &maximum)) {
        fprintf(stderr, "No valid numeric value found\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", maximum);
    return EXIT_SUCCESS;
}