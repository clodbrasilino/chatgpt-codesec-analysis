#include <stdio.h>

int sum_even_factors(int n) {
    if (n <= 0) {
        return 0;
    }
    int sum = 0;
    for (int i = 1; i * i <= n; i++) {
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
    printf("%d\n", sum_even_factors(num));
    return 0;
}