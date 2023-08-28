#include <stdio.h>

unsigned long long factorial(unsigned long long n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

unsigned long long findFirstFactorialDivisible(unsigned long long x) {
    unsigned long long i = 1;
    while (1) {
        if (factorial(i) % x == 0) {
            return i;
        }
        i++;
    }
}

int main() {
    unsigned long long x;
    printf("Enter the value of x: ");
    scanf("%llu", &x);

    unsigned long long result = findFirstFactorialDivisible(x);
    printf("The first natural number whose factorial is divisible by %llu is: %llu\n", x, result);
    return 0;
}