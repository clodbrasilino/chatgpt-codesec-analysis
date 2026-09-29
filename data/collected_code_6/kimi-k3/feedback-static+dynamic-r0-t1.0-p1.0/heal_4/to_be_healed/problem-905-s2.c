#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>

int64_t binomial_coefficient(int64_t n, int64_t k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n - k) {
        k = n - k;
    }
    int64_t result = 1;
    for (int64_t i = 0; i < k; i++) {
        if (result > INT64_MAX / (n - i)) {
            return -1;
        }
        result = result * (n - i) / (i + 1);
    }
    return result;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 70, got <no output>
  *  test case 1 failed: expected 252, got <no output>
  *  test case 2 failed: expected 6, got <no output>
  */

int64_t sum_of_squares(int64_t n) {
    if (n < 0) {
        return -1;
    }
    int64_t sum = 0;
    for (int64_t k = 0; k <= n; k++) {
        int64_t coeff = binomial_coefficient(n, k);
        if (coeff == -1 || coeff > INT64_MAX / coeff) {
            return -1;
        }
        int64_t square = coeff * coeff;
        if (sum > INT64_MAX - square) {
            return -1;
        }
        sum += square;
    }
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    int64_t n;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    errno = 0;
    n = strtoimax(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return 1;
    }
    
    int64_t result = sum_of_squares(n);
    if (result == -1) {
        return 1;
    }
    
    printf("%" PRId64 "\n", result);
    return 0;
}