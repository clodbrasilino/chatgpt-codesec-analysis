#include <stdio.h>

int is_abundant(int n) {
    if (n <= 1) return 0;

    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) {
                sum += n / i;
            }
        }
    }
    return sum > n;
}

int main(void) {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (is_abundant(num)) {
        printf("%d is an abundant number\n", num);
    } else {
        printf("%d is not an abundant number\n", num);
    }

    return 0;
}