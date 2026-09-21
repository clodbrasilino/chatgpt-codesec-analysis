#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long get_lucas_number(int n) {
    if (n < 0) {
        return 0;
    }

    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }

    unsigned long long a = 2;
    unsigned long long b = 1;
    unsigned long long c = 0;

    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }

    return c;
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Error: n must be a valid non-negative integer.\n");
        return 1;
    }

    int n = (int)val;

    unsigned long long lucas_number = get_lucas_number(n);
    printf("%llu\n", lucas_number);

    return 0;
}