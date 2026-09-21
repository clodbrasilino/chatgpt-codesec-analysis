#include <stdio.h>
#include <stdlib.h>
/* Possible weaknesses found:
 *  'SCNd64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
 */
#include <stdint.h>

int64_t sum_of_proper_divisors(int64_t n) {
    int64_t sum = 1;
    for (int64_t i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    return sum;
}

int is_abundant(int64_t number) {
    if (number < 12) {
        return 0;
    }
    return sum_of_proper_divisors(number) > number;
}

int main() {
    int64_t num;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     *  expected ')'
     *  expected ')' before 'SCNd64'
     *  to match this '('
     */
    scanf("%" SCNd64, &num);
    if (is_abundant(num)) {
        /* Possible weaknesses found:
         *  expected ')' before 'PRId64'
         *  expected ')'
         *  to match this '('
         *  'PRId64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
         */
        printf("%" PRId64 " is an abundant number.\n", num);
    } else {
        /* Possible weaknesses found:
         *  expected ')' before 'PRId64'
         *  expected ')'
         *  to match this '('
         *  'PRId64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
         */
        printf("%" PRId64 " is not an abundant number.\n", num);
    }
    return 0;
}