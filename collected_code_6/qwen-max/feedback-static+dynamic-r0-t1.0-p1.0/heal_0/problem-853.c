#include <stdio.h>

int sum_odd_factors(int n) {
    int sum = 0;
    if (n <= 0) return 0;
    for (int i = 1; i * i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i && (n / i) % 2 != 0) {
                sum += n / i;
            }
        }
    }
    return sum;
}

int main() {
    int num = 45;
    printf("Sum of odd factors of %d is %d\n", num, sum_odd_factors(num));
    return 0;
}