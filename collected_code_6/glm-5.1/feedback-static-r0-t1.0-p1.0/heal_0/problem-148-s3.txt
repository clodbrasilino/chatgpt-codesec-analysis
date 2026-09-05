#include <stdio.h>
#include <stdlib.h>

int digit_sum(long long n) {
    int sum = 0;
    if (n < 0) {
        n = -n;
    }
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

long long* divide_for_max_sum(long long n) {
    long long* result = (long long*)malloc(2 * sizeof(long long));
    if (result == NULL) {
        return NULL;
    }

    if (n < 1) {
        result[0] = 0;
        result[1] = n;
        return result;
    }

    result[0] = 0;
    result[1] = n;

    long long power = 1;
    while (power <= n) {
        long long a = n / power;
        long long b = n % power;
        if (a > 0 && b > 0) {
            int current_sum = digit_sum(a) + digit_sum(b);
            int max_sum = digit_sum(result[0]) + digit_sum(result[1]);
            if (current_sum > max_sum) {
                result[0] = a;
                result[1] = b;
            }
        }
        power *= 10;
    }

    return result;
}

int main() {
    long long n = 12345;
    long long* res = divide_for_max_sum(n);
    if (res != NULL) {
        printf("%lld %lld\n", res[0], res[1]);
        free(res);
    }
    return 0;
}