#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_sum_of_two_squares(uint64_t number)
{
    uint64_t left = 0;
    uint64_t right = 0;

    while (right <= number / (right + 1)) {
        ++right;
    }

    while (left <= right) {
        uint64_t left_square = left * left;
        uint64_t right_square = right * right;
        uint64_t remainder = number - right_square;

        if (left_square == remainder) {
            return true;
        }

        if (left_square < remainder) {
            ++left;
        } else if (right == 0) {
            break;
        } else {
            --right;
        }
    }

    return false;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    puts(is_sum_of_two_squares((uint64_t)value) ? "Yes" : "No");

    return EXIT_SUCCESS;
}