#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    
    long long a0 = 1;
    long long a1 = 1;
    int count = 0;
    long long result = -1;
    
    /* Possible weaknesses found:
     *  Condition 'is_prime(a0)' is always false
     *  Calling function 'is_prime' returns 0
     *  Condition 'is_prime(a0)' is always false [knownConditionTrueFalse]
     */
    if (is_prime(a0)) {
        count++;
        if (count == n) return a0;
    }
    /* Possible weaknesses found:
     *  Condition 'is_prime(a1)' is always false
     *  Calling function 'is_prime' returns 0
     *  Condition 'is_prime(a1)' is always false [knownConditionTrueFalse]
     */
    if (is_prime(a1)) {
        count++;
        if (count == n) return a1;
    }
    
    long long prev2 = a0;
    long long prev1 = a1;
    
    for (int i = 2; ; i++) {
        long long current = 2 * prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
        
        if (is_prime(current)) {
            count++;
            if (count == n) {
                result = current;
                break;
            }
        }
        
        if (current > 9223372036854775807LL / 2) {
            break;
        }
    }
    
    return result;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = nsw_prime(n);
    if (result == -1) {
        printf("Could not find the %dth NSW prime\n", n);
        return EXIT_FAILURE;
    }
    
    printf("The %dth NSW prime is: %lld\n", n, result);
    return EXIT_SUCCESS;
}