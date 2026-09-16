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

int main(void) {
    unsigned long long num1, num2;
    
    if (scanf("%llu %llu", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (num1 == 0 || num2 == 0) {
        fprintf(stderr, "Numbers must be positive\n");
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", lcm(num1, num2));
    
    return EXIT_SUCCESS;
}