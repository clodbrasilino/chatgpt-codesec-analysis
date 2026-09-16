#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

long long sum_primes(int n)
{
    if (n < 2) {
        return 0;
    }

    bool *is_prime = malloc((size_t)(n + 1) * sizeof(*is_prime));
    if (is_prime == NULL) {
        return -1;
    }

    for (int i = 0; i <= n; i++) {
        is_prime[i] = true;
    }
    is_prime[0] = false;
    is_prime[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    long long sum = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            sum += i;
        }
    }

    free(is_prime);
    return sum;
}

int main(void)
{
    int n;
    char input_buffer[128];
    char *end_ptr;

    printf("Enter a positive integer: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    long value = strtol(input_buffer, &end_ptr, 10);

    if (errno != 0 || end_ptr == input_buffer || *end_ptr != '\n' && *end_ptr != '\0') {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }

    if (value < 1 || value > INT_MAX) {
        fprintf(stderr, "Value out of valid range (1 to %d)\n", INT_MAX);
        return EXIT_FAILURE;
    }

    n = (int)value;
    long long result = sum_primes(n);

    if (result < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Sum of primes between 1 and %d: %lld\n", n, result);
    return EXIT_SUCCESS;
}