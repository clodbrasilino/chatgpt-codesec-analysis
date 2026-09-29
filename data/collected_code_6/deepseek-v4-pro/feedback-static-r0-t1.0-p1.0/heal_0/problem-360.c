#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t carol_number(unsigned int n) {
    if (n > 63) {
        fprintf(stderr, "Error: n must be <= 63 to avoid overflow\n");
        exit(EXIT_FAILURE);
    }
    uint64_t val = (1ULL << n) - 1ULL;
    return val * val - 2ULL;
}

int main(void) {
    unsigned int n;
    printf("Enter n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    uint64_t result = carol_number(n);
    printf("Carol number C%u = %llu\n", n, (unsigned long long)result);
    return 0;
}