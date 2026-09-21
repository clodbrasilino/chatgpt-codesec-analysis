#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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

int main(int argc, const char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    errno = 0;
    char *endptr;
    long n_long = strtol(argv[1], &endptr, 10);
    
    if (errno != 0 || *endptr != '\0' || argv[1] == endptr) {
        fprintf(stderr, "Error: Invalid numeric input.\n");
        return 1;
    }

    if (n_long < 0 || n_long > 93) {
        fprintf(stderr, "Error: n must be between 0 and 93 to prevent overflow.\n");
        return 1;
    }

    int n = (int)n_long;
    unsigned long long lucas_number = get_lucas_number(n);
    printf("%llu\n", lucas_number);

    return 0;
}