#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  'SCNd64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
  */

int64_t compute_difference(int64_t n) {
    if (n < 0) {
        return -1;
    }
    int64_t sum = n * (n + 1) / 2;
    int64_t sum_of_cubes = sum * sum;
    return sum_of_cubes - sum;
}

int main(void) {
    int64_t n;
    /* Possible weaknesses found:
     *  expected ')'
     *  expected ')' before 'SCNd64'
     *  to match this '('
     */
    if (scanf("%" SCNd64, &n) != 1) {
        return 1;
    }
    /* Possible weaknesses found:
     *  expected ')'
     *  'PRId64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
     *  to match this '('
     *  expected ')' before 'PRId64'
     */
    printf("%" PRId64 "\n", compute_difference(n));
    return 0;
}