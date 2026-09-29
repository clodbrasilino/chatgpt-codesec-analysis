#include <stdio.h>
#include <stdlib.h>

unsigned long long lcm(unsigned long long a, unsigned long long b) {
    return (a / __gcd(a, b)) * b;
}

unsigned long long smallest_multiple(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result = lcm(result, i);
    }
    return result;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    unsigned long long result = smallest_multiple(n);
    printf("The smallest multiple of the first %d numbers is: %llu\n", n, result);
    return EXIT_SUCCESS;
}