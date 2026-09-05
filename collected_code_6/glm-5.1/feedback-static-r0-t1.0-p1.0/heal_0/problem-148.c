#include <stdio.h>
#include <stdlib.h>

int digit_sum(long long n) {
    int s = 0;
    if (n < 0) {
        n = -n;
    }
    while (n > 0) {
        s += n % 10;
        n /= 10;
    }
    return s;
}

long long find_max_sum_split(long long n, long long *a, long long *b) {
    if (n <= 0) {
        *a = 0;
        *b = 0;
        return 0;
    }

    long long max_sum = -1;
    long long best_a = 0;
    long long best_b = 0;

    long long m = 10;
    while (m <= n) {
        long long x = n / m;
        long long y = n % m;
        int current_sum = digit_sum(x) + digit_sum(y);
        if (current_sum > max_sum) {
            max_sum = current_sum;
            best_a = x;
            best_b = y;
        }
        m *= 10;
    }

    *a = best_a;
    *b = best_b;
    return max_sum;
}

int main(void) {
    long long n = 1234567;
    long long a, b;
    long long result = find_max_sum_split(n, &a, &b);
    printf("%lld: %lld + %lld = %lld\n", n, a, b, result);
    
    n = 1000;
    result = find_max_sum_split(n, &a, &b);
    printf("%lld: %lld + %lld = %lld\n", n, a, b, result);

    n = -9876;
    result = find_max_sum_split(n, &a, &b);
    printf("%lld: %lld + %lld = %lld\n", n, a, b, result);

    n = 0;
    result = find_max_sum_split(n, &a, &b);
    printf("%lld: %lld + %lld = %lld\n", n, a, b, result);

    return 0;
}