#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long octagonal_number(int n) {
    if (n <= 0) {
        return -1;
    }
    return (long long)n * (3 * n - 2);
}

int main(int argc, const char *argv[]) {
    int n;
    long long result;
    char *endptr;
    long val;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    errno = 0;
    val = strtol(argv[1], &endptr, 10);

    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Error: number out of range\n");
        return 1;
    }

    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Error: invalid integer\n");
        return 1;
    }

    n = (int)val;

    if (n <= 0) {
        fprintf(stderr, "Error: n must be a positive integer\n");
        return 1;
    }

    result = octagonal_number(n);

    if (result < 0) {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    printf("%lld\n", result);
    return 0;
}