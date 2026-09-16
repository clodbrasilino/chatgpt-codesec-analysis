#include <limits.h>
#include <stdint.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  'SCNu32' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
  */

static uint32_t set_leftmost_unset_bit(uint32_t value)
{
    /* Possible weaknesses found:
     *  'UINT32_WIDTH' undeclared (first use in this function); did you mean 'UINT_WIDTH'?
     *  use of undeclared identifier 'UINT32_WIDTH'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    for (uint32_t mask = UINT32_C(1) << (UINT32_WIDTH - 1); mask != 0; mask >>= 1) {
        if ((value & mask) == 0) {
            return value | mask;
        }
    }

    return value;
}

int main(void)
{
    uint32_t value;

    /* Possible weaknesses found:
     *  expected ')'
     *  expected ')' before 'SCNu32'
     *  to match this '('
     */
    if (scanf("%" SCNu32, &value) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    /* Possible weaknesses found:
     *  to match this '('
     *  expected ')'
     *  expected ')' before 'PRIu32'
     *  'PRIu32' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
     */
    printf("%" PRIu32 "\n", set_leftmost_unset_bit(value));
    return 0;
}