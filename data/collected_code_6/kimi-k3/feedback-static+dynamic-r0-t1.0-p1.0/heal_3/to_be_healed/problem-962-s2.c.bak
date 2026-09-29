#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  'SCNd64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
  */

int64_t sum_even_natural(int64_t l, int64_t r)
{
    if (l > r || r < 2)
    {
        return 0;
    }

    if (l < 2)
    {
        l = 2;
    }

    int64_t first = (l % 2 == 0) ? l : l + 1;
    int64_t last = (r % 2 == 0) ? r : r - 1;

    if (first > last)
    {
        return 0;
    }

    int64_t count = (last - first) / 2 + 1;
    return count * (first + last) / 2;
}

int main(void)
{
    int64_t l, r;

    /* Possible weaknesses found:
     *  expected ')'
     *  to match this '('
     *  expected ')' before 'SCNd64'
     */
    if (scanf("%" SCNd64 " %" SCNd64, &l, &r) != 2)
    {
        return 1;
    }

    /* Possible weaknesses found:
     *  expected ')'
     *  'PRId64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
     *  to match this '('
     *  expected ')' before 'PRId64'
     */
    printf("%" PRId64 "\n", sum_even_natural(l, r));
    return 0;
}