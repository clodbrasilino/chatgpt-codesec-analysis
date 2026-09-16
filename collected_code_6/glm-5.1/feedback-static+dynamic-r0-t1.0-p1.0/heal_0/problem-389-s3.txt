#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long find_lucas(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }
    if ((unsigned long long)n > ULLONG_MAX) {
        return 0;
    }
    unsigned long long a = 2;
    unsigned long long b = 1;
    unsigned long long c;
    for (int i = 2; i <= n; i++) {
        if (a > ULLONG_MAX - b) {
            return 0;
        }
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        return 1;
    }
    n = atoi(argv[1]);
    if (n < 0) {
        return 1;
    }
    unsigned long long result = find_lucas(n);
    if (result == 0 && n > 1) {
        return 1;
    }
    printf("%llu\n", result);
    return 0;
}