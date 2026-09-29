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

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        return 1;
    }
    char *endptr;
    errno = 0;
    long long val = strtoll(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || val <= 0) {
        return 1;
    }
    int result = find_factorial_divisible(val);
    if (result == -1) {
        return 1;
    }
    printf("%d\n", result);
    return 0;
}