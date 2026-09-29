#include <stdio.h>

int sum_common_divisors(int a, int b) {
    if (a <= 0 || b <= 0) {
        return 0;
    }
    int min = a < b ? a : b;
    int sum = 0;
    for (int i = 1; i <= min; i++) {
        if (a % i == 0 && b % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int a, b;
    if (scanf("%d %d", &a, &b) == 2) {
        int result = sum_common_divisors(a, b);
        printf("%d\n", result);
    }
    return 0;
}