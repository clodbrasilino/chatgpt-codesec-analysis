#include <stdio.h>
#include <math.h>

long long find_smallest_triangular_index(int n) {
    if (n <= 0) {
        return -1;
    }
    if (n == 1) {
        return 3;
    }
    long long min_val = 1;
    for (int i = 1; i < n; ++i) {
        min_val *= 10;
    }
    long long c = 2LL * min_val;
    if (c < 0) {
        return -1;
    }
    double k = ceil((-1.0 + sqrt(1.0 + 8.0 * (double)c)) / 2.0);
    if (k > (double)9223372036854775807.0) {
        return -1;
    }
    return (long long)k;
}

int main() {
    int n;
    if (scanf("%d", &n) == 1) {
        long long result = find_smallest_triangular_index(n);
        printf("%lld\n", result);
        return 0;
    }
    return 1;
}