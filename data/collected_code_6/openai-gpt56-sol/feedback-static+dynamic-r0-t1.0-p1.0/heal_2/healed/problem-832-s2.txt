#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool extract_maximum(const char *input, uint64_t *maximum)
{
    const char *cursor;
    uint64_t max_value = 0;
    bool found = false;

    if (input == NULL || maximum == NULL) {
        return false;
    }

    cursor = input;

    while (*cursor != '\0') {
        char *end;
        uintmax_t value;

        if (*cursor < '0' || *cursor > '9') {
            ++cursor;
            continue;
        }

        errno = 0;
        value = strtoumax(cursor, &end, 10);

        if (end == cursor) {
            ++cursor;
            continue;
        }

        if (errno == ERANGE || value > UINT64_MAX) {
            fprintf(stderr, "Numeric value is out of range\n");
            return false;
        }

        if (!found || (uint64_t)value > max_value) {
            max_value = (uint64_t)value;
            found = true;
        }

        cursor = end;
    }

    if (found) {
        *maximum = max_value;
    }

    return found;
}

int main(int argc, char *const argv[])
{
    uint64_t maximum;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s \"text containing numbers\"\n",
                program_name);
        return EXIT_FAILURE;
    }

    if (!extract_maximum(argv[1], &maximum)) {
        fprintf(stderr, "No valid numeric value found\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", maximum);
    return EXIT_SUCCESS;
}