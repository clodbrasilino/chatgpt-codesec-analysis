#include <stdio.h>
#include <math.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  'SCNd64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
  */

int64_t sum_even_factors(int64_t n) {
    if (n <= 0) return 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'n%2!=0' is not redundant
     */
    if (n % 2 != 0) return 0;

    int64_t sum = 0;
    int64_t temp = n;
    while (temp % 2 == 0) {
        sum += 2;
        temp /= 2;
    }
    if (temp != 1) {
        sum += 2;
    }

    int64_t limit = (int64_t)sqrt((double)n);
    for (int64_t i = 3; i <= limit; i += 2) {
        if (n % i == 0) {
            if (i % 2 == 0) sum += i;
            int64_t counterpart = n / i;
            if (counterpart != i && counterpart % 2 == 0) sum += counterpart;
        }
    }

    /* Possible weaknesses found:
     *  Condition 'n%2==0' is always true
     *  Condition 'n%2==0' is always true [knownConditionTrueFalse]
     */
    if (n % 2 == 0 && n != 2) sum += n;
    return sum;
}

int main(void) {
    int64_t number;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  to match this '('
     *  expected ')' before 'SCNd64'
     *  expected ')'
     */
    if (scanf("%" SCNd64, &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    /* Possible weaknesses found:
     *  'PRId64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
     *  to match this '('
     *  expected ')' before 'PRId64'
     *  expected ')'
     */
    printf("Sum of even factors: %" PRId64 "\n", sum_even_factors(number));
    return 0;
}