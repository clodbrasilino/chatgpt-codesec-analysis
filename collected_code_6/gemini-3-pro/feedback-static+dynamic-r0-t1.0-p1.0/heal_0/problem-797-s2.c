#include <stdio.h>
#include <stdlib.h>

long long sum_odd_numbers(long long l, long long r) {
    if (l > r || l < 0) {
        return -1;
    }

    if (l % 2 == 0) {
        l++;
    }
    if (r % 2 == 0) {
        r--;
    }

    if (l > r) {
        return 0;
    }

    long long n = ((r - l) / 2) + 1;
    return n * (l + r) / 2;
}

int main() {
    long long l, r;
    long long sum;

    if (scanf("%lld %lld", &l, &r) != 2) {
        return EXIT_FAILURE;
    }

    sum = sum_odd_numbers(l, r);

    if (sum == -1) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", sum);

    return EXIT_SUCCESS;
}