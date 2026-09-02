#include <stdio.h>
#include <stdlib.h>

unsigned long long jacobsthal(unsigned int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    unsigned long long a = 0, b = 1;
    for (unsigned int i = 2; i <= n; ++i) {
        unsigned long long c = a + 2 * b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    unsigned int n;
    printf("Enter the value of n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = jacobsthal(n);
    printf("The %u-th Jacobsthal number is: %llu\n", n, result);
    return EXIT_SUCCESS;
}