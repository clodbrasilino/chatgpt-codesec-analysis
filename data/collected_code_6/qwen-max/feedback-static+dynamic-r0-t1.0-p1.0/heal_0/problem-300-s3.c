#include <stdio.h>
#include <stdlib.h>

unsigned long long combination(unsigned long long n, unsigned long long k) {
    if (k > n) return 0;
    if (k * 2 > n) k = n - k;
    if (k == 0) return 1;

    unsigned long long result = n;
    for (unsigned long long i = 2; i <= k; ++i) {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}

unsigned long long count_sequences(unsigned int n) {
    unsigned long long count = 0;
    for (unsigned int k = 0; k <= n; ++k) {
        count += combination(n, k) * combination(n, k);
    }
    return count;
}

int main() {
    unsigned int n;
    printf("Enter the value of n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = count_sequences(n);
    printf("The count of all binary sequences of length 2n such that sum of first n bits is same as sum of last n bits: %llu\n", result);

    return EXIT_SUCCESS;
}