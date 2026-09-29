#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

bool is_prime(long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

long ns_williams(long n) {
    long a = 1, b = 1;
    for (long i = 1; ; i++) {
        long next = 2 * b + a;
        a = b;
        b = next;
        if (is_prime(next)) {
            if (--n == 0) return next;
        }
    }
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long n = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || n <= 0 || n > LONG_MAX) {
        fprintf(stderr, "Input must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    long result = ns_williams(n);
    printf("%ld\n", result);

    return EXIT_SUCCESS;
}