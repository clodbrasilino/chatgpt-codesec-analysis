#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool divisor_count_is_odd(uint64_t number)
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

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed_value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || parsed_value == 0 || parsed_value > UINT64_MAX) {
        fprintf(stderr, "Invalid positive integer\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", divisor_count_is_odd((uint64_t)parsed_value) ? "odd" : "even");
    return EXIT_SUCCESS;
}