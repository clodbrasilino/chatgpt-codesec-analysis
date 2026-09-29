#include <stdio.h>
#include <stdlib.h>

long long largest_prime_factor(long long n) {
    if (n < 2) {
        return 0;
    }
    long long largest = 0;
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
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long long number = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0' || number < 0) {
        fprintf(stderr, "Error: Invalid input. Must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    long long result = largest_prime_factor(number);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}