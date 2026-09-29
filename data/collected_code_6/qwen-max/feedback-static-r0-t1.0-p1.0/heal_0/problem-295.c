#include <stdio.h>

int sum_of_divisors(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    int result = sum_of_divisors(number);
    printf("Sum of divisors of %d is %d\n", number, result);
    return 0;
}