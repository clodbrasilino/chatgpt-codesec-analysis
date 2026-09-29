#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_perfect_square(uint64_t number)
{
    uint64_t low = 0;
    uint64_t high = UINT64_C(4294967295);

    if (number < high) {
        high = number;
    }

    while (low <= high) {
        uint64_t mid = low + (high - low) / 2;

        if (mid != 0 && mid > number / mid) {
            high = mid - 1;
        } else {
            uint64_t square = mid * mid;

            if (square == number) {
                return true;
            }

            low = mid + 1;
        }
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end = NULL;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (input[0] == '-' ||
        (input[0] != '\0' && input[1] == '-' &&
         (input[0] == ' ' || input[0] == '\t' || input[0] == '\n' ||
          input[0] == '\r' || input[0] == '\f' || input[0] == '\v'))) {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    puts(is_perfect_square((uint64_t)value) ? "Yes" : "No");
    return EXIT_SUCCESS;
}