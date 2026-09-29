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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(is_perfect_square((uint64_t)value) ? "Yes" : "No");
    return EXIT_SUCCESS;
}