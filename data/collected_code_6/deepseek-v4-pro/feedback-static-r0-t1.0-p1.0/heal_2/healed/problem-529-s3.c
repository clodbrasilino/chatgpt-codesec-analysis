#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t jacobsthal_lucas(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) return 2;
    if (n == 1) return 1;
    
    uint64_t a = 2;
    uint64_t b = 1;
    uint64_t result = 0;
    
    for (int i = 2; i <= n; i++) {
        result = b + 2 * a;
        a = b;
        b = result;
    }
    
    return result;
}

int main(int argc, char *const argv[]) {
    int n = 10;
    
    if (argc > 1) {
        char *endptr;
        long val = strtol(argv[1], &endptr, 10);
        if (endptr != argv[1] && *endptr == '\0' && val >= 0 && val <= 64) {
            n = (int)val;
        } else {
            fprintf(stderr, "Invalid input. Using default n=%d\n", n);
        }
    }
    
    uint64_t result = jacobsthal_lucas(n);
    printf("Jacobsthal-Lucas number at position %d: %llu\n", n, (unsigned long long)result);
    
    return 0;
}