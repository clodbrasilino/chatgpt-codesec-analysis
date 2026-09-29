#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  'SCNu64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
  */

static bool has_odd_parity(uint64_t value)
{
    bool odd = false;

    while (value != UINT64_C(0)) {
        odd = !odd;
        value &= value - UINT64_C(1);
    }

    return odd;
}

int main(void)
{
    uint64_t value = UINT64_C(0);

    /* Possible weaknesses found:
     *  expected ')'
     *  expected ')' before 'SCNu64'
     *  to match this '('
     */
    if (scanf("%" SCNu64, &value) != 1) {
        return 1;
    }

    if (printf("%s\n", has_odd_parity(value) ? "Odd parity" : "Even parity") < 0) {
        return 1;
    }

    return 0;
}