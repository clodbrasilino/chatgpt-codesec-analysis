#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int find_factorial_divisible(long long x) {
    if (x <= 0) {
        return -1;
    }
    int n = 1;
    long long factorial = 1;
    while (factorial % x != 0) {
        n++;
        if (n > 20) {
            return -1;
        }
        factorial *= n;
    }
    return n;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return 1;
    }
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || val <= 0 || val > LLONG_MAX) {
        return 1;
    }
    long long x = val;
    int result = find_factorial_divisible(x);
    if (result == -1) {
        return 1;
    }
    printf("%d\n", result);
    return 0;
}