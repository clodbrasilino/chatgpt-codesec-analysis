#include <stdio.h>

long long count_squares(int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    if (m > n) {
        int temp = m;
        m = n;
        n = temp;
    }
    unsigned long long a = (unsigned long long)m;
    unsigned long long b = (unsigned long long)n;
    return (long long)(a * (a + 1) * (3 * b - a + 1) / 6);
}

int main() {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2) {
        return 1;
    }
    printf("%lld\n", count_squares(m, n));
    return 0;
}