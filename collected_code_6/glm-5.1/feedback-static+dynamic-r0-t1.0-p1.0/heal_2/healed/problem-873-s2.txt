#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long fibonacci(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    if (n == 0) {
        return 0;
    }
    long long a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val < 0 || val > INT_MAX || errno == ERANGE) {
        return EXIT_FAILURE;
    }
    int n = (int)val;
    long long result = fibonacci(n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}