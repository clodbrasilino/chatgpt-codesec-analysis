#include <stdio.h>
#include <stdint.h>
#include <errno.h>

int jacobsthal(unsigned int n, uint64_t *result) {
    if (result == NULL) {
        return EINVAL;
    }
    
    if (n == 0) {
        *result = 0;
        return 0;
    }
    if (n == 1) {
        *result = 1;
        return 0;
    }
    
    uint64_t prev2 = 0;
    uint64_t prev1 = 1;
    uint64_t current = 0;
    
    for (unsigned int i = 2; i <= n; i++) {
        current = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    *result = current;
    return 0;
}

int main(void) {
    unsigned int n;
    uint64_t result;
    
    printf("Enter n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    int status = jacobsthal(n, &result);
    if (status != 0) {
        fprintf(stderr, "Error calculating Jacobsthal number\n");
        return 1;
    }
    
    printf("Jacobsthal(%u) = %llu\n", n, (unsigned long long)result);
    return 0;
}