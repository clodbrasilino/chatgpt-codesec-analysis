#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int count_digits(unsigned long long n) {
    unsigned int c = 0;
    if (n == 0) return 1;
    while (n != 0) {
        c++;
        n /= 10;
    }
    return c;
}

unsigned long long safe_add(unsigned long long a, unsigned long long b, int *err) {
    if (a > ULLONG_MAX - b) {
        *err = 1;
        return 0;
    }
    *err = 0;
    return a + b;
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        return 1;
    }
    char *end1, *end2;
    unsigned long long a = strtoull(argv[1], &end1, 10);
    unsigned long long b = strtoull(argv[2], &end2, 10);
    if (*end1 != '\0' || *end2 != '\0') {
        return 1;
    }
    int err;
    unsigned long long sum = safe_add(a, b, &err);
    if (err) {
        return 1;
    }
    unsigned int digits = count_digits(sum);
    printf("%u\n", digits);
    return 0;
}