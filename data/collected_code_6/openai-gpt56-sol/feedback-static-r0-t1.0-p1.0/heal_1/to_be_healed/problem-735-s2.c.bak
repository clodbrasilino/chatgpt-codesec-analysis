#include <limits.h>
#include <stdint.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  'SCNu32' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
  */

static uint32_t toggle_inner_bits(uint32_t number)
{
    const unsigned int bit_count = sizeof(number) * CHAR_BIT;
    const uint32_t inner_mask = (UINT32_MAX >> 1U) & ~(UINT32_C(1));

    if (bit_count <= 2U) {
        return number;
    }

    return number ^ inner_mask;
}

int main(void)
{
    uint32_t number;

    /* Possible weaknesses found:
     *  expected ')' before 'SCNu32'
     *  expected ')'
     *  to match this '('
     */
    if (scanf("%" SCNu32, &number) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    /* Possible weaknesses found:
     *  to match this '('
     *  expected ')'
     *  'PRIu32' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
     *  expected ')' before 'PRIu32'
     */
    printf("%" PRIu32 "\n", toggle_inner_bits(number));
    return 0;
}