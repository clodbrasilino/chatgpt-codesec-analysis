#include <stdio.h>
#include <stdlib.h>

static int sum_proper_divisors(int n) {
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
    int *divisor_sums = malloc((limit + 1) * sizeof(int));
    if (divisor_sums == NULL) {
        return 0;
    }
    for (int i = 0; i <= limit; i++) {
        divisor_sums[i] = sum_proper_divisors(i);
    }
    long long total_sum = 0;
    for (int a = 1; a <= limit; a++) {
        int b = divisor_sums[a];
        if (b <= limit && b > a) {
            if (divisor_sums[b] == a) {
                total_sum += a + b;
            }
        }
    }
    free(divisor_sums);
    return total_sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int limit = 10000;
    if (argc == 2) {
        long long val = atoll(argv[1]);
        if (val > 0 && val <= 1000000) {
            limit = (int)val;
        } else {
            return 1;
        }
    }
    long long result = sum_amicable_numbers(limit);
    printf("%lld\n", result);
    return 0;
}