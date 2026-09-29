#include <stdio.h>
#include <stdlib.h>

int sum_of_proper_divisors(int n) {
    if (n < 2) return 0;
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

int sum_of_amicable_numbers(int limit) {
    if (limit < 1) return 0;
    int *div_sums = (int *)malloc((limit + 1) * sizeof(int));
    if (div_sums == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= limit; i++) {
        div_sums[i] = sum_of_proper_divisors(i);
    }
    int total_sum = 0;
    for (int a = 2; a <= limit; a++) {
        int b = div_sums[a];
        if (b > 1 && b <= limit && b != a && div_sums[b] == a) {
            total_sum += a;
        }
    }
    free(div_sums);
    return total_sum;
}

int main(void) {
    int upper_limit = 10000;
    int result = sum_of_amicable_numbers(upper_limit);
    printf("%d\n", result);
    return 0;
}