#include <stdio.h>
#include <stdlib.h>

long long find_nth_non_multiple(long long n, long long k) {
    if (n <= 0 || k <= 1) {
        exit(EXIT_FAILURE);
    }
    long long full_cycles = (n - 1) / (k - 1);
    long long remainder = (n - 1) % (k - 1);
    return full_cycles * k + remainder + 1;
}

int main(void) {
    long long n, k;
    if (scanf("%lld %lld", &n, &k) != 2) {
        return EXIT_FAILURE;
    }
    long long result = find_nth_non_multiple(n, k);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}