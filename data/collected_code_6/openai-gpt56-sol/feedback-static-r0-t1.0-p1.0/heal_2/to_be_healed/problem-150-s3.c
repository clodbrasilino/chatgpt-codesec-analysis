#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_present(uint64_t number)
{
    uint64_t low = 0;
    uint64_t high = UINT32_MAX;

    while (low <= high) {
        uint64_t middle = low + (high - low) / 2;
        uint64_t square = middle * middle;

        if (square == number) {
            return true;
        }

        if (middle > number / middle) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }

    return false;
}

int main(void)
{
    uintmax_t value;
    int result;

    errno = 0;
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    result = scanf("%" SCNuMAX, &value);

    if (result != 1 || errno == ERANGE || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    int ch;
    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch != EOF) {
        return EXIT_FAILURE;
    }

    puts(is_present((uint64_t)value) ? "Present" : "Not present");
    return EXIT_SUCCESS;
}