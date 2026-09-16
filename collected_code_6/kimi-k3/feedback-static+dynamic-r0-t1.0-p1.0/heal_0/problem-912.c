#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t lobb_number(int n, int m) {
    if (n < 0 || m < 0 || m > n) {
        return 0;
    }
    
    uint64_t result = 1;
    for (int i = 1; i <= m; i++) {
        if (result > UINT64_MAX / (uint64_t)(n + i)) {
            return 0;
        }
        result *= (uint64_t)(n + i);
        result /= (uint64_t)i;
    }
    
    if (result > UINT64_MAX / (uint64_t)(2 * m + 1)) {
        return 0;
    }
    result *= (uint64_t)(2 * m + 1);
    
    if (result % (uint64_t)(n + m + 1) != 0) {
        return 0;
    }
    result /= (uint64_t)(n + m + 1);
    
    return result;
}

int main(void) {
    int n, m;
    
    if (scanf("%d %d", &n, &m) != 2) {
        return EXIT_FAILURE;
    }
    
    uint64_t result = lobb_number(n, m);
    printf("%" PRIu64 "\n", result);
    
    return EXIT_SUCCESS;
}