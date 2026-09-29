#include <stdio.h>

int sum_odd_factors(int n) {
    if (n <= 0) {
        return 0;
    }

    int sum = 0;

    for (int i = 1; i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
        }
    }

    return sum;
}

int main(void) {
    int num;

    if (scanf("%d", &num) != 1) {
        return 1;
    }

    int result = sum_odd_factors(num);

    if (printf("%d\n", result) < 0) {
        return 1;
    }

    return 0;
}