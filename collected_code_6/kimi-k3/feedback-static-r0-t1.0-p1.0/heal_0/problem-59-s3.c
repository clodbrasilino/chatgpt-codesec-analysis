#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t octagonal_number(int64_t n) {
    return n * (3 * n - 2);
}

int main(void) {
    int64_t n;
    
    if (scanf("%" SCNd64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    printf("%" PRId64 "\n", octagonal_number(n));
    
    return EXIT_SUCCESS;
}