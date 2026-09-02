#include <stdio.h>
#include <stdlib.h>

unsigned long gcd(unsigned long a, unsigned long b) {
    while (b != 0) {
        unsigned long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

unsigned long lcm(unsigned long a, unsigned long b) {
    return a / gcd(a, b) * b;
}

unsigned long smallest_multiple(int n) {
    unsigned long result = 1;
    for (int i = 2; i <= n; i++) {
        result = lcm(result, i);
    }
    return result;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("%lu\n", smallest_multiple(n));
    return EXIT_SUCCESS;
}