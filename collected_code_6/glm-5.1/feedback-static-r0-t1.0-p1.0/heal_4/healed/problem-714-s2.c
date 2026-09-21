#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

int count_distinct_prime_powers(int64_t n) {
    if (n <= 1) {
        return 0;
    }
    int count = 0;
    int64_t p = 2;
    while (p * p <= n) {
        if (n % p == 0) {
            count++;
            while (n % p == 0) {
                n /= p;
            }
        }
        p += (p == 2) ? 1 : 2;
    }
    if (n > 1) {
        count++;
    }
    return count;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }
    if (argv[1][0] == '\0') {
        fprintf(stderr, "Invalid input. Please provide a positive integer.\n");
        return 1;
    }
    char *endptr;
    errno = 0;
    int64_t val = strtoll(argv[1], &endptr, 10);
    if (errno == ERANGE || *endptr != '\0' || val <= 0) {
        fprintf(stderr, "Invalid input. Please provide a positive integer.\n");
        return 1;
    }
    int result = count_distinct_prime_powers(val);
    printf("%d\n", result);
    return 0;
}