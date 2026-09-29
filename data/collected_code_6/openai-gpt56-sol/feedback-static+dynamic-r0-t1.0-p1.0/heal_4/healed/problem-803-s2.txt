#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_perfect_square(uint64_t number)
{
    uint64_t low = 0;
    uint64_t high = number < UINT32_MAX ? number : UINT32_MAX;

    while (low <= high) {
        uint64_t middle = low + (high - low) / 2;

        if (middle != 0 && middle > number / middle) {
            high = middle - 1;
        } else {
            uint64_t square = middle * middle;

            if (square == number) {
                return true;
            }

            low = middle + 1;
        }
    }

    return false;
}

int main(void)
{
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] != '\0') {
        return EXIT_FAILURE;
    } else {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            return EXIT_FAILURE;
        }

        if (ch == EOF && ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    char *start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        if (printf("False\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    bool valid = end != start &&
                 *end == '\0' &&
                 errno != ERANGE &&
                 value <= UINT64_MAX;

    bool result = valid && is_perfect_square((uint64_t)value);

    if (printf("%s\n", result ? "True" : "False") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}