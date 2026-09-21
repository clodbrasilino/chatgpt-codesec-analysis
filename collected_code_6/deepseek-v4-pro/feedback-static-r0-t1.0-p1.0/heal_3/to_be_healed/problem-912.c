#include <stdio.h>
#include <stdlib.h>
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
    if (m == 0) return 0;
    if (n > m - 1) return 0;

    unsigned long long numerator = (2 * n + 1) * binomial(2 * m, m + n);
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
    char *input = NULL;
    size_t input_size = 0;
    ssize_t bytes_read;

    printf("Enter m and n: ");
    bytes_read = getline(&input, &input_size, stdin);
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (input[bytes_read - 1] == '\n') {
        input[bytes_read - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'bytes_read' is assigned a value that is never used. [unreadVariable]
         */
        bytes_read--;
    }

    char *endptr_m = NULL;
    char *endptr_n = NULL;
    errno = 0;
    unsigned long long temp_m = strtoull(input, &endptr_m, 10);
    if (errno == ERANGE || endptr_m == input) {
        fprintf(stderr, "Invalid input format\n");
        free(input);
        return EXIT_FAILURE;
    }

    while (*endptr_m == ' ') {
        endptr_m++;
    }

    if (*endptr_m == '\0') {
        fprintf(stderr, "Invalid input format\n");
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    unsigned long long temp_n = strtoull(endptr_m, &endptr_n, 10);
    if (errno == ERANGE || endptr_n == endptr_m) {
        fprintf(stderr, "Invalid input format\n");
        free(input);
        return EXIT_FAILURE;
    }

    while (*endptr_n == ' ') {
        endptr_n++;
    }

    if (*endptr_n != '\0') {
        fprintf(stderr, "Invalid input format\n");
        free(input);
        return EXIT_FAILURE;
    }

    m = temp_m;
    n = temp_n;

    free(input);

    unsigned long long result = lobb_number(m, n);
    printf("L(%llu, %llu) = %llu\n", m, n, result);

    return EXIT_SUCCESS;
}