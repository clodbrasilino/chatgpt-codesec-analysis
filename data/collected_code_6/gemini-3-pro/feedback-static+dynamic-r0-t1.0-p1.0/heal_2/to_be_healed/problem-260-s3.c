#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_prime(long long int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for (long long int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

long long int nth_nsw_prime(int n) {
    if (n <= 0) {
        return -1; 
    }
    int count = 0;
    long long int s0 = 1;
    
    /* Possible weaknesses found:
     *  Condition 'is_prime(s0)' is always false [knownConditionTrueFalse]
     *  Condition 'is_prime(s0)' is always false
     *  Calling function 'is_prime' returns 0
     */
    if (is_prime(s0)) {
        count++;
        if (count == n) return s0;
    }

    long long int s1 = 1;
    /* Possible weaknesses found:
     *  Condition 'is_prime(s1)' is always false [knownConditionTrueFalse]
     *  Condition 'is_prime(s1)' is always false
     *  Calling function 'is_prime' returns 0
     */
    if (is_prime(s1)) {
        count++;
        if (count == n) return s1;
    }

    /* Possible weaknesses found:
     *  Variable 's_n' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 's_n' can be reduced. [variableScope]
     */
    long long int s_n = 0;
    while (1) {
        if (s1 > (9223372036854775807LL - s0) / 2) {
            return -1;
        }
        s_n = 2 * s1 + s0;
        
        if (is_prime(s_n)) {
            count++;
            if (count == n) {
                return s_n;
            }
        }
        s0 = s1;
        s1 = s_n;
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        return EXIT_FAILURE;
    }

    long long int result = nth_nsw_prime(n);
    if (result == -1) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);
    return EXIT_SUCCESS;
}