#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  'PRIu64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
  */

uint64_t sum_of_fifth_powers(int n) {
    uint64_t sum = 0;
    for (int i = 1; i <= n; i++) {
        int even = 2 * i;
        sum += (uint64_t)even * even * even * even * even;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Input error\n");
        return 1;
    }
    if (n < 1) {
        fprintf(stderr, "n must be a positive integer\n");
        return 1;
    }

    uint64_t result = sum_of_fifth_powers(n);
    /* Possible weaknesses found:
     *  to match this '('
     *  expected ')'
     *  expected ')' before 'PRIu64'
     */
    printf("The sum of the fifth power of the first %d even natural numbers is: %" PRIu64 "\n", n, result);
    return 0;
}