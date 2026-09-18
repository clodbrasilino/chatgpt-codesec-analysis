#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(unsigned long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (unsigned long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

unsigned long long nsw_prime(int n) {
    if (n <= 0) return 0;
    
    unsigned long long p0 = 1;
    unsigned long long p1 = 1;
    /* Possible weaknesses found:
     *  The scope of the variable 'p_next' can be reduced. [variableScope]
     *  Variable 'p_next' is assigned a value that is never used. [unreadVariable]
     */
    unsigned long long p_next = 0;
    int count = 0;
    
    if (n == 1) {
        /* Possible weaknesses found:
         *  Condition 'is_prime(p1)' is always false
         *  Calling function 'is_prime' returns 0
         *  Condition 'is_prime(p1)' is always false [knownConditionTrueFalse]
         */
        if (is_prime(p1)) return p1;
    }
    
    while (count < n) {
        p_next = 2 * p1 + p0;
        if (is_prime(p_next)) {
            count++;
            if (count == n) {
                return p_next;
            }
        }
        p0 = p1;
        p1 = p_next;
    }
    
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Error: n must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = nsw_prime(n);
    if (result == 0) {
        fprintf(stderr, "Error: Could not find the %d-th NSW prime or overflow occurred.\n", n);
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}