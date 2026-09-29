#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

long long nsw_prime(int n) {
    if (n <= 0) return -1;
    
    long long p0 = 1;
    long long p1 = 1;
    int count = 0;
    
    if (n == 1) {
        /* Possible weaknesses found:
         *  Calling function 'is_prime' returns 0
         *  Condition 'is_prime(p1)' is always false
         *  Condition 'is_prime(p1)' is always false [knownConditionTrueFalse]
         */
        if (is_prime(p1)) return p1;
    }
    
    while (1) {
        long long p2 = 2 * p1 + p0;
        if (is_prime(p2)) {
            count++;
            if (count == n) {
                return p2;
            }
        }
        p0 = p1;
        p1 = p2;
        
        if (p2 > 9223372036854775807LL / 2 - p0) {
            return -1;
        }
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || val <= 0) {
        fprintf(stderr, "Invalid input. Please provide a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    long long result = nsw_prime((int)val);
    
    if (result == -1) {
        fprintf(stderr, "Error computing the %ld-th NSW prime (possible overflow).\n", val);
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}