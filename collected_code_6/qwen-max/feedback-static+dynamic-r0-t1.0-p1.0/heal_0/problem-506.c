#include <stdio.h>
#include <stdlib.h>

unsigned long factorial(unsigned int n) {
    if (n == 0) return 1;
    unsigned long result = 1;
    for (unsigned int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

unsigned long permutation_coefficient(unsigned int n, unsigned int k) {
    if (k > n) return 0;
    return factorial(n) / factorial(n - k);
}

int main() {
    unsigned int n, k;
    printf("Enter the value of n: ");
    scanf("%u", &n);
    printf("Enter the value of k: ");
    scanf("%u", &k);

    unsigned long result = permutation_coefficient(n, k);
    printf("P(%u, %u) = %lu\n", n, k, result);

    return 0;
}