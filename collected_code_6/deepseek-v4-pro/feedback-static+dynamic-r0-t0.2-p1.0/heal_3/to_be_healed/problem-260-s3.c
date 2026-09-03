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
    /* Possible weaknesses found:
     *  Assuming that condition 'n<=0' is not redundant
     */
    if (n <= 0) return -1;
    
    long long a0 = 1;
    long long a1 = 1;
    /* Possible weaknesses found:
     *  Assignment 'count=0', assigned value is 0
     */
    int count = 0;
    
    /* Possible weaknesses found:
     *  Condition 'is_prime(a0)' is always false
     *  Condition 'count<n' is always true
     *  Calling function 'is_prime' returns 0
     *  Condition 'count<n' is always true [knownConditionTrueFalse]
     *  Condition 'is_prime(a0)' is always false [knownConditionTrueFalse]
     */
    if (count < n && is_prime(a0)) {
        count++;
        if (count == n) return a0;
    }
    
    /* Possible weaknesses found:
     *  Condition 'count<n' is always true
     *  Calling function 'is_prime' returns 0
     *  Condition 'count<n' is always true [knownConditionTrueFalse]
     *  Condition 'is_prime(a1)' is always false [knownConditionTrueFalse]
     *  Condition 'is_prime(a1)' is always false
     */
    if (count < n && is_prime(a1)) {
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