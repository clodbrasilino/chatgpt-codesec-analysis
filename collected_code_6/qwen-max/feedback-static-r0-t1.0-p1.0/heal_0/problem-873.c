#include <stdio.h>

unsigned long long fibonacci(unsigned int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    unsigned int n = 10;
    printf("Fibonacci(%u) = %llu\n", n, fibonacci(n));
    return 0;
}