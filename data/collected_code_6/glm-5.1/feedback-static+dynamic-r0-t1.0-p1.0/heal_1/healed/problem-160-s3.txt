#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int find_solution(long long a, long long b, long long n, long long *x, long long *y) {
    if (a == 0 && b == 0) {
        return (n == 0) ? 0 : -1;
    }
    if (a == 0) {
        if (n % b == 0) {
            *x = 0;
            *y = n / b;
            return 0;
        }
        return -1;
    }
    if (b == 0) {
        if (n % a == 0) {
            *x = n / a;
            *y = 0;
            return 0;
        }
        return -1;
    }
    long long limit = (n > 0 ? n : -n);
    for (long long i = -limit; i <= limit; i++) {
        if ((n - a * i) % b == 0) {
            *x = i;
            *y = (n - a * i) / b;
            return 0;
        }
    }
    return -1;
}

long long parse_long_long(const char *str) {
    char *endptr;
    errno = 0;
    long long val = strtoll(str, &endptr, 10);
    if ((errno == ERANGE && (val == LLONG_MAX || val == LLONG_MIN)) || (errno != 0 && val == 0)) {
        return LLONG_MAX;
    }
    if (endptr == str) {
        return LLONG_MAX;
    }
    if (*endptr != '\0') {
        return LLONG_MAX;
    }
    return val;
}

int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <n>\n", argv[0]);
        return 1;
    }
    long long a = parse_long_long(argv[1]);
    long long b = parse_long_long(argv[2]);
    long long n = parse_long_long(argv[3]);
    if (a == LLONG_MAX || b == LLONG_MAX || n == LLONG_MAX) {
        fprintf(stderr, "Invalid integer input or out of range\n");
        return 1;
    }
    long long x, y;
    if (find_solution(a, b, n, &x, &y) == 0) {
        printf("%lld %lld\n", x, y);
        return 0;
    } else {
        printf("No solution\n");
        return 1;
    }
}