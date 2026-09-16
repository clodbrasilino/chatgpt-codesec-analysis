#include <stdio.h>
#include <stdlib.h>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long long lcm(unsigned long long a, unsigned long long b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return (a / gcd(a, b)) * b;
}

unsigned long long smallest_multiple(unsigned int n) {
    if (n == 0) return 0;
    
    unsigned long long result = 1;
    for (unsigned int i = 2; i <= n; i++) {
        result = lcm(result, i);
    }
    return result;
}

int main(void) {
    unsigned int n = 20;
    unsigned long long result;

    result = smallest_multiple(n);
    printf("The smallest multiple of the first %u numbers is %llu\n", n, result);

    return 0;
}