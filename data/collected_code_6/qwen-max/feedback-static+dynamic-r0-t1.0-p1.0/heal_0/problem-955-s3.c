#include <stdio.h>
#include <stdbool.h>

bool is_abundant(int n) {
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            if (i * i != n) {
                sum += i + n / i;
            } else {
                sum += i;
            }
        }
    }
    return sum > n;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    if (is_abundant(number)) {
        printf("%d is an abundant number.\n", number);
    } else {
        printf("%d is not an abundant number.\n", number);
    }
    return 0;
}