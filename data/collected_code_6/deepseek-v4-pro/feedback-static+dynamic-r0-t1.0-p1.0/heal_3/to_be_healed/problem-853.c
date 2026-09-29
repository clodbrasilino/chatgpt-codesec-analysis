#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 24, got <no output>
  *  test case 1 failed: expected 13, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

int64_t sum_of_odd_factors(int64_t n) {
    int64_t sum = 0;
    
    if (n <= 0) {
        return 0;
    }
    
    if (n > INT64_MAX / 2) {
        double sqrt_val = sqrt((double)n);
        if (sqrt_val > (double)INT64_MAX) {
            return -1;
        }
    }
    
    double sqrt_n = sqrt((double)n);
    if (sqrt_n > 9223372036854775807.0) {
        return -1;
    }
    
    int64_t limit = (int64_t)sqrt_n;
    
    if (limit < 0) {
        return -1;
    }
    
    for (int64_t i = 1; i <= limit; i++) {
        if (n % i == 0) {
            if (i % 2 == 1) {
                if (sum > INT64_MAX - i) {
                    return -1;
                }
                sum += i;
            }
            
            int64_t paired_factor = n / i;
            if (paired_factor != i && paired_factor % 2 == 1) {
                if (sum > INT64_MAX - paired_factor) {
                    return -1;
                }
                sum += paired_factor;
            }
        }
    }
    
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    
    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }
    
    char *endptr;
    errno = 0;
    int64_t number = (int64_t)strtoll(input, &endptr, 10);
    
    if (errno == ERANGE || number <= 0 || endptr == input || *endptr != '\n') {
        printf("Invalid input\n");
        return 1;
    }
    
    int64_t result = sum_of_odd_factors(number);
    if (result < 0) {
        printf("Overflow detected\n");
        return 1;
    }
    
    printf("Sum of odd factors: %" PRId64 "\n", result);
    
    return 0;
}