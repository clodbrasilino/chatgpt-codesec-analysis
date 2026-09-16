#include <stdio.h>
#include <stdlib.h>

unsigned long long factorial(unsigned int n) {
    if (n == 0) return 1;
    unsigned long long fact = 1;
    for (unsigned int i = 1; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}

unsigned long long permutation(unsigned int n, unsigned int k) {
    if (k > n) return 0;
    return factorial(n) / factorial(n - k);
}

int main() {
    unsigned int n = 5, k = 3;
    printf("P(%u, %u) = %llu\n", n, k, permutation(n, k));
    return 0;
}