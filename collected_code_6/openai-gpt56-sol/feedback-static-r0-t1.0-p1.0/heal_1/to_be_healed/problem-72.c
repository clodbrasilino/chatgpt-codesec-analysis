#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static bool is_difference_of_two_squares(int64_t number)
{
    uint64_t magnitude;

    if (number < 0) {
        magnitude = (uint64_t)(-(number + 1)) + 1U;
    } else {
        magnitude = (uint64_t)number;
    }

    return magnitude % 4U != 2U;
}

int main(void)
{
    int64_t number;
    char extra;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &number) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (scanf(" %c", &extra) == 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(is_difference_of_two_squares(number) ? "Yes" : "No");
    return 0;
}