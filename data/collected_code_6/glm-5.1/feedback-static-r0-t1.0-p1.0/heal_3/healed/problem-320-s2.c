#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_difference(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    unsigned long long sum = (unsigned long long)n * (n + 1) / 2;
    unsigned long long sum_sq = (unsigned long long)n * (n + 1) * (2 * n + 1) / 6;
    unsigned long long sq_sum = sum * sum;
    return sq_sum - sum_sq;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    char *endptr;
    unsigned long long val = strtoull(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > 4294967295ULL) {
        fprintf(stderr, "Error: n is out of range for unsigned int\n");
        return 1;
    }
    unsigned int n = (unsigned int)val;
    unsigned long long result = calculate_difference(n);
    printf("%llu\n", result);
    return 0;
}