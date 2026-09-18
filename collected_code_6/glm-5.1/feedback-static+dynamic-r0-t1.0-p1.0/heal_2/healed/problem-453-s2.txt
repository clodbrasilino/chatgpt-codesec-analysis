#include <stdio.h>
#include <stdint.h>

int64_t sum_even_factors(int n) {
    if (n <= 0) {
        return 0;
    }
    int64_t sum = 0;
    for (int i = 1; (int64_t)i * i <= n; i++) {
        if (n % i == 0) {
            if (i % 2 == 0) {
                sum += i;
            }
            int j = n / i;
            if (j != i) {
                if (j % 2 == 0) {
                    sum += j;
                }
            }
        }
    }
    return sum;
}

int main() {
    int num;
    if (scanf("%d", &num) != 1) {
        return 1;
    }
    printf("%" PRId64 "\n", sum_even_factors(num));
    return 0;
}