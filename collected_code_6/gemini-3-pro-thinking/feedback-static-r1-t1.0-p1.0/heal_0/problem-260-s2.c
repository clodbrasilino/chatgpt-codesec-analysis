#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

int nth_nsw_prime(uint32_t n, uint64_t *result) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        *result = 1;
        return 1;
    }
    if (n == 2) {
        *result = 7;
        return 1;
    }

    uint64_t a = 1;
    uint64_t b = 7;
    uint64_t c;

    for (uint32_t i = 3; i <= n; i++) {
        if (b > (UINT64_MAX / 6)) {
            return 0;
        }
        c = 6 * b - a;
        a = b;
        b = c;
    }

    *result = b;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0') {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr;
    long n_in = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || endptr == argv[1] || n_in <= 0 || n_in > UINT32_MAX) {
        return EXIT_FAILURE;
    }

    uint64_t nsw_val;
    if (!nth_nsw_prime((uint32_t)n_in, &nsw_val)) {
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", (unsigned long long)nsw_val) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}