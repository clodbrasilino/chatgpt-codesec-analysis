#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

long long sum_of_prime_divisors(long long n) {
    if (n <= 1) {
        return 0;
    }
    long long sum = 0;
    long long original = n;
    if (n % 2 == 0) {
        sum += 2;
        while (n % 2 == 0) {
            n /= 2;
        }
    }
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        if (n != original) {
            sum += n;
        } else {
            sum += original;
        }
    }
    return sum;
}

int main(int argc, char * const argv[const]) {
    long long num;
    if (argc == 2) {
        if (strnlen(argv[1], 256) >= 256) {
            return 1;
        }
        char *endptr;
        num = strtoll(argv[1], &endptr, 10);
        if (*endptr != '\0' || num < 0) {
            return 1;
        }
    } else if (argc == 1) {
        char *buffer = NULL;
        size_t len = 0;
        ssize_t read = getline(&buffer, &len, stdin);
        if (read == -1) {
            return 1;
        }
        char *endptr;
        num = strtoll(buffer, &endptr, 10);
        while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
            endptr++;
        }
        if (*endptr != '\0' || num < 0) {
            free(buffer);
            return 1;
        }
        free(buffer);
    } else {
        return 1;
    }
    long long result = sum_of_prime_divisors(num);
    printf("%lld\n", result);
    return 0;
}