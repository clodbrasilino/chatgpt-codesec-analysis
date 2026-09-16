#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_product_of_two_squares(uint64_t number)
{
    uint64_t low = 0;
    uint64_t high = number < UINT64_C(4294967295)
                        ? number
                        : UINT64_C(4294967295);

    while (low <= high) {
        uint64_t mid = low + (high - low) / 2;
        uint64_t square = mid * mid;

        if (square == number) {
            return true;
        }

        if (square < number) {
            low = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            high = mid - 1;
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

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno != 0 || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    puts(is_product_of_two_squares((uint64_t)value) ? "Yes" : "No");
    return EXIT_SUCCESS;
}