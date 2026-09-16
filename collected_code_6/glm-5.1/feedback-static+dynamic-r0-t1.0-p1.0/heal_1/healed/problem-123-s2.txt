#include <stdio.h>
#include <stdlib.h>

int sum_divisors(int n) {
    if (n <= 1) {
        return 0;
    }
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    return sum;
}

long long sum_amicable_numbers(int limit) {
    if (limit <= 1) {
        return 0;
    }
    long long total_sum = 0;
    int *sums = (int *)malloc((limit + 1) * sizeof(int));
    if (sums == NULL) {
        return 0;
    }
    for (int i = 1; i <= limit; i++) {
        sums[i] = sum_divisors(i);
    }
    for (int a = 1; a <= limit; a++) {
        int b = sums[a];
        if (b <= limit && b > a && sums[b] == a) {
            total_sum += a;
            total_sum += b;
        }
    }
    free(sums);
    sums = NULL;
    return total_sum;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return 1;
    }
    long long val = atoll(argv[1]);
    if (val < 0 || val > 2147483647) {
        return 1;
    }
    int limit = (int)val;
    long long result = sum_amicable_numbers(limit);
    printf("%lld\n", result);
    return 0;
}