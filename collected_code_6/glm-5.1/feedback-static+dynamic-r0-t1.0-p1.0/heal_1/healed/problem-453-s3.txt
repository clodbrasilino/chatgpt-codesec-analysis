#include <stdio.h>
#include <limits.h>

long long sum_even_factors(int n) {
    long long sum = 0;
    if (n <= 0 || n % 2 != 0) {
        return 0;
    }
    for (int i = 2; (long long)i * i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
            int complement = n / i;
            if (complement != i && complement % 2 == 0) {
                sum += complement;
            }
        }
    }
    return sum;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    long long result = sum_even_factors(n);
    printf("%lld\n", result);
    return 0;
}