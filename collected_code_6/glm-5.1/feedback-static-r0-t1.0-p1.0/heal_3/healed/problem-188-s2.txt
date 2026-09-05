#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int check_product_of_two_squares(long long n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    long long i;
    for (i = 1; i * i <= n / i; i++) {
        if (n % (i * i) == 0) {
            long long q = n / (i * i);
            long long sq = (long long)sqrt((double)q);
            if (sq * sq == q || (sq + 1) * (sq + 1) == q) {
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char const * const argv[]) {
    long long n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }
    char *endptr;
    n = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (check_product_of_two_squares(n)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}