#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t sum_squares_binomial(int n) {
    if (n < 0) {
        return UINT64_MAX;
    }
    
    if (n > 66) {
        return UINT64_MAX;
    }
    
    uint64_t coefficient = 1;
    uint64_t sum = 0;
    
    for (int k = 0; k <= n; k++) {
        uint64_t square = coefficient * coefficient;
        if (square > UINT64_MAX - sum) {
            return UINT64_MAX;
        }
        sum += square;
        
        if (k == n) break;
        
        uint64_t numerator = coefficient * (n - k);
        if (numerator / coefficient != (uint64_t)(n - k)) {
            return UINT64_MAX;
        }
        
        uint64_t quotient = numerator / (k + 1);
        /* Possible weaknesses found:
         * UBSan: division by zero (AFL crash: id:000000,sig:06,src:000000,time:79,execs:52,op:havoc,rep:8)
         */
        if (quotient > UINT64_MAX / ((k + 2) <= (n - k) ? 1 : 0)) {
            return UINT64_MAX;
        }
        
        coefficient = quotient;
    }
    
    return sum;
}

uint64_t binomial_coefficient(int n, int k) {
    if (k < 0 || k > n || n < 0) {
        return 0;
    }
    
    if (k > n - k) {
        k = n - k;
    }
    
    uint64_t result = 1;
    
    for (int i = 0; i < k; i++) {
        uint64_t product = result * (n - i);
        if (result != 0 && product / result != (uint64_t)(n - i)) {
            return UINT64_MAX;
        }
        result = product / (i + 1);
    }
    
    return result;
}

uint64_t sum_squares_binomial_direct(int n) {
    if (n < 0) {
        return UINT64_MAX;
    }
    
    if (n > 66) {
        return UINT64_MAX;
    }
    
    uint64_t sum = 0;
    
    for (int k = 0; k <= n; k++) {
        uint64_t coeff = binomial_coefficient(n, k);
        if (coeff == UINT64_MAX) {
            return UINT64_MAX;
        }
        
        uint64_t square = coeff * coeff;
        if (square > UINT64_MAX - sum) {
            return UINT64_MAX;
        }
        sum += square;
    }
    
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000004,time:2523,execs:1403,op:havoc,rep:8; likely memory-safety defect
  */

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    if (n > 66) {
        fprintf(stderr, "n too large, results would overflow\n");
        return EXIT_FAILURE;
    }
    
    uint64_t result = sum_squares_binomial(n);
    if (result == UINT64_MAX) {
        fprintf(stderr, "Overflow in computation\n");
        return EXIT_FAILURE;
    }
    
    uint64_t verification = sum_squares_binomial_direct(n);
    if (verification == UINT64_MAX) {
        fprintf(stderr, "Overflow in verification\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of squares of binomial coefficients for n=%d: %" PRIu64 "\n", n, result);
    printf("Verification: %" PRIu64 "\n", verification);
    
    return EXIT_SUCCESS;
}