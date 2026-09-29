#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  'SCNu64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
  */

static bool differ_by_one_bit(uint64_t first, uint64_t second)
{
    const uint64_t difference = first ^ second;

    return difference != UINT64_C(0) &&
           (difference & (difference - UINT64_C(1))) == UINT64_C(0);
}

int main(void)
{
    uint64_t first = 0;
    uint64_t second = 0;

    /* Possible weaknesses found:
     *  expected ')' before 'SCNu64'
     *  to match this '('
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     *  expected ')'
     */
    if (scanf("%" SCNu64 " %" SCNu64, &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(differ_by_one_bit(first, second) ? "Yes" : "No");
    return 0;
}