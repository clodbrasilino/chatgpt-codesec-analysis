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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    unsigned int n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    unsigned long long val = strtoull(argv[1], NULL, 10);
    if (val > 4294967295ULL) {
        fprintf(stderr, "Error: n is out of range for unsigned int\n");
        return 1;
    }
    n = (unsigned int)val;
    unsigned long long result = calculate_difference(n);
    printf("%llu\n", result);
    return 0;
}