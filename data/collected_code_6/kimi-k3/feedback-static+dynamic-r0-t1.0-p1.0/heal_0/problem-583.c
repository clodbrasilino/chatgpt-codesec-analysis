#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

uint64_t catalan(unsigned int n) {
    if (n > 35) {
        return 0;
    }
    
    uint64_t result = 1;
    
    for (unsigned int i = 0; i < n; i++) {
        if (result > UINT64_MAX / (4 * i + 2)) {
            return 0;
        }
        result = result * (4 * i + 2) / (i + 2);
    }
    
    return result;
}

int main(void) {
    unsigned int n;
    
    if (scanf("%u", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    uint64_t result = catalan(n);
    printf("%lu\n", (unsigned long)result);
    
    return EXIT_SUCCESS;
}