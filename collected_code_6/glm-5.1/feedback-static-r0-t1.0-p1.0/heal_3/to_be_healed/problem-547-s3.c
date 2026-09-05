#include <stdio.h>
#include <stdlib.h>

unsigned int hamming_distance(unsigned int a, unsigned int b) {
    unsigned int xor_val = a ^ b;
    unsigned int distance = 0;
    while (xor_val) {
        distance += xor_val & 1;
        xor_val >>= 1;
    }
    return distance;
}

unsigned long long sum_hamming_distances_consecutive(unsigned int n) {
    unsigned long long total_sum = 0;
    if (n == 0) {
        return 0;
    }
    for (unsigned int i = 0; i < n; i++) {
        total_sum += hamming_distance(i, i + 1);
    }
    return total_sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    unsigned int n = 0;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    unsigned long long val = strtoull(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > 4294967295ULL) {
        fprintf(stderr, "Invalid input. Must be a non-negative integer within unsigned int range.\n");
        return EXIT_FAILURE;
    }
    n = (unsigned int)val;
    unsigned long long result = sum_hamming_distances_consecutive(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}