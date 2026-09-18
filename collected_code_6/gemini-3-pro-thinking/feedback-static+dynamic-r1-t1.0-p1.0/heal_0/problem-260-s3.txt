#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t nth_nsw_prime(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    
    uint64_t a = 1;
    uint64_t b = 1;
    uint64_t c = 0;
    
    for (int i = 2; i <= n; i++) {
        if (b > (UINT64_MAX - a) / 2) {
            return 0;
        }
        c = 2 * b + a;
        a = b;
        b = c;
    }
    
    return b;
}

int main(void) {
    int n = 0;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    uint64_t result = nth_nsw_prime(n);
    
    if (result == 0 && (n < 0 || n > 1)) {
        return EXIT_FAILURE;
    }
    
    printf("%" PRIu64 "\n", result);
    
    return EXIT_SUCCESS;
}