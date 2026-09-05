#include <stdio.h>
#include <stdlib.h>

long find_max_k(long x, long y, long n) {
    if (x <= 0 || n < 0) {
        exit(EXIT_FAILURE);
    }
    if (y >= x) {
        exit(EXIT_FAILURE);
    }
    long q = (n - y) / x;
    long k = q * x + y;
    return k;
}

int main(void) {
    long x, y, n;
    if (scanf("%ld %ld %ld", &x, &y, &n) != 3) {
        return EXIT_FAILURE;
    }
    long result = find_max_k(x, y, n);
    printf("%ld\n", result);
    return EXIT_SUCCESS;
}