#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

uint64_t find_nth_carol_number(int n) {
    if (n < 1) {
        exit(EXIT_FAILURE);
    }
    if (n > 31) {
        exit(EXIT_FAILURE);
    }
    uint64_t result = ((uint64_t)1 << n) - ((uint64_t)1 << (n - 1)) - 1;
    return result;
}

int main(void) {
    int n = 5;
    uint64_t carol_number = find_nth_carol_number(n);
    printf("%" PRIu64 "\n", carol_number);
    return 0;
}