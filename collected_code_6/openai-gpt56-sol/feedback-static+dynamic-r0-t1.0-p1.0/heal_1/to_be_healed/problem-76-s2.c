#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    uint64_t side;
    uint64_t other;
    uint64_t first;
    uint64_t second;

    if (result == NULL || width == 0U || height == 0U) {
        return 0;
    }

    side = width < height ? width : height;
    other = width < height ? height : width;

    if (side == UINT64_MAX) {
        return 0;
    }

    first = side * (side + 1U) / 2U;
    second = side * (side - 1U) * (side + 1U) / 3U;

    if (other > 0U && first > UINT64_MAX / other) {
        return 0;
    }

    *result = other * first - second;
    return 1;
}

int main(void)
{
    uint64_t width;
    uint64_t height;
    uint64_t result;
    int matched;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    matched = scanf("%" SCNu64 " %" SCNu64, &width, &height);
    if (matched != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!count_squares(width, height, &result)) {
        fputs("Invalid dimensions or arithmetic overflow\n", stderr);
        return 1;
    }

    printf("%" PRIu64 "\n", result);
    return 0;
}