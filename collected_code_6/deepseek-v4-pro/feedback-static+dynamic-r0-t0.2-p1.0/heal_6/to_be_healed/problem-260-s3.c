#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

static bool is_prime(long long n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

static long long nsw_prime(int n) {
    if (n <= 0) return -1;
    
    /* Possible weaknesses found:
     *  'a0' is assigned value '1' here.
     */
    long long a0 = 1;
    /* Possible weaknesses found:
     *  'a1' is assigned value '1' here.
     */
    long long a1 = 1;
    int count = 0;
    
    /* Possible weaknesses found:
     *  The comparison 'a0 > 1' is always false.
     *  The comparison 'a0 > 1' is always false. [knownConditionTrueFalse]
     */
    if (a0 > 1 && is_prime(a0)) {
        count++;
        if (count == n) return a0;
    }
    
    /* Possible weaknesses found:
     *  The comparison 'a1 > 1' is always false. [knownConditionTrueFalse]
     *  The comparison 'a1 > 1' is always false.
     */
    if (a1 > 1 && is_prime(a1)) {
        count++;
        if (count == n) return a1;
    }
    
    long long prev2 = a0;
    long long prev1 = a1;
    
    while (count < n) {
        if (prev1 > (LLONG_MAX - prev2) / 2) return -1;
        long long current = 2 * prev1 + prev2;
        
        if (is_prime(current)) {
            count++;
            if (count == n) return current;
        }
        
        prev2 = prev1;
        prev1 = current;
    }
    
    return -1;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = nsw_prime(n);
    if (result < 0) {
        fprintf(stderr, "Unable to compute\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}