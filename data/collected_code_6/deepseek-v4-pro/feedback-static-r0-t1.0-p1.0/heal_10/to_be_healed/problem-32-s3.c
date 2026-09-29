#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

long long largest_prime_factor(long long n) {
    if (n < 2) {
        return -1;
    }

    long long largest = -1;

    while (n % 2 == 0) {
        largest = 2;
        n /= 2;
    }

    for (long long i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            largest = i;
            n /= i;
        }
    }

    if (n > 2) {
        largest = n;
    }

    return largest;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long long num = strtoll(argv[1], &endptr, 10);

    if (errno == ERANGE && (num == LLONG_MAX || num == LLONG_MIN)) {
        fprintf(stderr, "Error: Number out of range\n");
        return 1;
    }

    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Error: Invalid number\n");
        return 1;
    }

    if (num < 0) {
        fprintf(stderr, "Error: Number must be non-negative\n");
        return 1;
    }

    long long result = largest_prime_factor(num);

    if (result == -1) {
        printf("No prime factors found for %lld\n", num);
    } else {
        printf("Largest prime factor of %lld is %lld\n", num, result);
    }

    return 0;
}