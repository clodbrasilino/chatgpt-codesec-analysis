#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

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
        if (result > UINT64_MAX / (n - i)) {
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
    if (m == 0) return 0;
    
    if (n > m - 1) return 0;

    unsigned long long binom = binomial(2 * m, m + n);
    
    if (binom > UINT64_MAX / (2 * n + 1)) {
        fprintf(stderr, "Overflow in lobb number numerator calculation\n");
        exit(EXIT_FAILURE);
    }
    
    unsigned long long numerator = (2 * n + 1) * binom;
    unsigned long long denominator = m + n + 1;
    
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
    char input[128];
    
    printf("Enter m and n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == EOF && ferror(stdin)) {
                clearerr(stdin);
            }
        }
        if (len == sizeof(input) - 1) {
            fprintf(stderr, "Input line too long\n");
            return EXIT_FAILURE;
        }
    }

    char *endptr;
    errno = 0;
    unsigned long long val1 = strtoull(input, &endptr, 10);
    if (errno == ERANGE || endptr == input) {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    while (*endptr == ' ' || *endptr == '\t') endptr++;
    
    char *next = endptr;
    errno = 0;
    unsigned long long val2 = strtoull(next, &endptr, 10);
    if (errno == ERANGE || endptr == next) {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    while (*endptr == ' ' || *endptr == '\t') endptr++;
    if (*endptr != '\0' && *endptr != '\n') {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    m = val1;
    n = val2;
    
    unsigned long long result = lobb_number(m, n);
    printf("L(%llu, %llu) = %llu\n", m, n, result);
    
    return EXIT_SUCCESS;
}