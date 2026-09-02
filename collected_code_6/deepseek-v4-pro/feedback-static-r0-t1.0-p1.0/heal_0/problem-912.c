#include <stdio.h>
#include <stdlib.h>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

unsigned long long binomial(unsigned long long n, unsigned long long k) {
    if (k > n) return 0;
    if (k > n - k) k = n - k;
    unsigned long long result = 1;
    for (unsigned long long i = 0; i < k; i++) {
        if (result > (18446744073709551615ULL) / (n - i)) {
            fprintf(stderr, "Overflow in binomial calculation\n");
            exit(EXIT_FAILURE);
        }
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

unsigned long long lobb_number(unsigned long long m, unsigned long long n) {
    if (m == 0 && n == 0) return 1;
    if (n == 0) return 0;
    if (m > 0 && (n == 0)) return 0;
    if (m == 0) return 0;
    
    if (n > m - 1) return 0;
    
    unsigned long long numerator = (2 * n + 1) * binomial(2 * m, m + n);
    unsigned long long denominator = m + n + 1;
    
    if (denominator == 0) {
        fprintf(stderr, "Division by zero\n");
        exit(EXIT_FAILURE);
    }
    
    if (numerator % denominator != 0) {
        unsigned long long g = gcd(numerator, denominator);
        numerator /= g;
        denominator /= g;
        if (denominator != 1) {
            fprintf(stderr, "Result is not an integer\n");
            exit(EXIT_FAILURE);
        }
        return numerator;
    }
    
    return numerator / denominator;
}

int main(void) {
    unsigned long long m, n;
    char input[256];
    
    printf("Enter m and n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    if (sscanf(input, "%llu %llu", &m, &n) != 2) {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = lobb_number(m, n);
    printf("L(%llu, %llu) = %llu\n", m, n, result);
    
    return EXIT_SUCCESS;
}