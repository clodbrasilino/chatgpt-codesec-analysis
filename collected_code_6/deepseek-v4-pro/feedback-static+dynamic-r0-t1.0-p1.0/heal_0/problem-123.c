#include <stdio.h>
#include <stdlib.h>

static int sum_of_divisors(int n) {
    if (n <= 1) return 0;
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

int sum_amicable_numbers(int limit) {
    if (limit < 1) return 0;
    int *sums = (int *)calloc((size_t)limit + 1, sizeof(int));
    if (sums == NULL) return 0;

    for (int i = 1; i <= limit; i++) {
        sums[i] = sum_of_divisors(i);
    }

    int total = 0;
    for (int a = 2; a <= limit; a++) {
        int b = sums[a];
        if (b > a && b <= limit && sums[b] == a) {
            total += a + b;
        }
    }

    free(sums);
    return total;
}

int main(void) {
    int limit = 10000;
    printf("Sum of amicable numbers up to %d: %d\n", limit,
           sum_amicable_numbers(limit));
    return 0;
}