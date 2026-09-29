#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_in_sequence(uint64_t number)
{
    uint64_t low = 0;
    uint64_t high = UINT32_MAX;

    while (low <= high) {
        uint64_t middle = low + (high - low) / 2;
        uint64_t square = middle * middle;

        if (square == number) {
            return true;
        }

        if (square < number) {
            low = middle + 1;
        } else {
            if (middle == 0) {
                break;
            }
            high = middle - 1;
        }
    }

    return false;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    char *newline = strchr(input, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else if (!feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(is_in_sequence((uint64_t)value) ? "Present" : "Not present");

    return EXIT_SUCCESS;
}