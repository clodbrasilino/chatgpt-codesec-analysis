#include <stdio.h>

int sum_of_divisors(int num) {
    int sum = 0;
    for (int i = 1; i <= num; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    printf("Sum of divisors: %d\n", sum_of_divisors(number));
    return 0;
}