#include <stdio.h>
#include <stdlib.h>

unsigned long long pell(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    unsigned long long a = 0;
    unsigned long long b = 1;
    for (int i = 2; i <= n; i++) {
        unsigned long long c = 2 * b + a;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return 1;
    }
    long val = strtol(argv[1], NULL, 10);
    if (val < 0 || val > 36) {
        return 1;
    }
    printf("%llu\n", pell((int)val));
    return 0;
}