#include <stdio.h>
#include <stdlib.h>

int is_abundant(int n) {
    if (n < 1) {
        return 0;
    }

    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            int other = n / i;
            if (other != i) {
                sum += other;
            }
        }
    }

    if (n == 1) {
        sum = 1;
    }

    return sum > n;
}

int main(void) {
    int numbers[] = {12, 18, 28, 6, 1, 0, -5, 20, 24, 30};
    int count = sizeof(numbers) / sizeof(numbers[0]);

    for (int i = 0; i < count; i++) {
        if (is_abundant(numbers[i])) {
            printf("%d is abundant\n", numbers[i]);
        } else {
            printf("%d is not abundant\n", numbers[i]);
        }
    }

    return 0;
}