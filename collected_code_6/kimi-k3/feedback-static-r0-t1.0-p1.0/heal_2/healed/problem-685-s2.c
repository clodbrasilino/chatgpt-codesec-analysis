#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

bool is_prime(int num) {
    if (num < 2) {
        return false;
    }
    if (num == 2) {
        return true;
    }
    if (num % 2 == 0) {
        return false;
    }
    for (int i = 3; i <= num / i; i += 2) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

long long sum_of_primes(int n) {
    if (n < 2) {
        return 0;
    }
    long long sum = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            sum += i;
        }
    }
    return sum;
}

int main(void) {
    int n;
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_len;
    char *endptr;
    long val;

    printf("Enter a positive integer n: ");
    
    read_len = getline(&buffer, &buffer_size, stdin);
    if (read_len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (read_len > 0 && buffer[read_len - 1] == '\n') {
        buffer[read_len - 1] = '\0';
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < 1) {
        fprintf(stderr, "Invalid input: out of range\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    n = (int)val;
    printf("Sum of prime numbers between 1 and %d is: %lld\n", n, sum_of_primes(n));
    
    free(buffer);
    return EXIT_SUCCESS;
}