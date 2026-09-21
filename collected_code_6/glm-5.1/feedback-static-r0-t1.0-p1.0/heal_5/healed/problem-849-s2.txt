#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_prime_divisors(unsigned long n) {
    unsigned long long sum = 0;
    unsigned long remaining = n;

    if (remaining > 1 && remaining % 2 == 0) {
        sum += 2;
        while (remaining % 2 == 0) {
            remaining /= 2;
        }
    }

    for (unsigned long i = 3; i * i <= remaining; i += 2) {
        if (remaining % i == 0) {
            sum += i;
            while (remaining % i == 0) {
                remaining /= i;
            }
        }
    }

    if (remaining > 2) {
        sum += remaining;
    }

    return sum;
}

int main(int argc, char * const argv[]) {
    char *endptr;
    unsigned long n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return 1;
    }

    n = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || n == 0) {
        fprintf(stderr, "Error: Invalid input. Must be a positive integer.\n");
        return 1;
    }

    printf("%llu\n", sum_prime_divisors(n));

    return 0;
}