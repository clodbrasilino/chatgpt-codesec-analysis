#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int next_perfect_square(uint64_t number, uint64_t *result)
{
    uint64_t low = 0;
    uint64_t high = UINT32_MAX;
    uint64_t root = 0;

    if (result == NULL) {
        return 0;
    }

    while (low <= high) {
        uint64_t middle = low + (high - low) / 2;
        uint64_t square = middle * middle;

        if (square <= number) {
            root = middle;
            low = middle + 1;
        } else {
            if (middle == 0) {
                break;
            }
            high = middle - 1;
        }
    }

    if (root == UINT32_MAX) {
        return 0;
    }

    ++root;
    *result = root * root;
    return 1;
}

int main(void)
{
    uint64_t number;
    uint64_t result;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &number) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!next_perfect_square(number, &result)) {
        fputs("No representable next perfect square\n", stderr);
        return 1;
    }

    printf("%" PRIu64 "\n", result);
    return 0;
}