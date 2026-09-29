#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_sum_of_two_squares(uint64_t number)
{
    uint64_t left = 0;
    uint64_t right = number;

    while (right > 0 && right > number / right) {
        --right;
    }

    while (left <= right) {
        const uint64_t left_square = left * left;
        const uint64_t right_square = right * right;
        const uint64_t remainder = number - left_square;

        if (right_square == remainder) {
            return true;
        }

        if (right_square > remainder) {
            --right;
        } else {
            ++left;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid non-negative integer\n");
        return EXIT_FAILURE;
    }

    if (input > UINT64_MAX) {
        fprintf(stderr, "Integer is out of range\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", is_sum_of_two_squares((uint64_t)input) ? "Yes" : "No");
    return EXIT_SUCCESS;
}