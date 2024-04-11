#include <stdio.h>

int sum_of_divisors(int num) {
    int sum = 0;
    for(int i = 1; i <= num; i++) {
        if(num % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int check_sum_of_divisors(int num1, int num2) {
    int sum1 = sum_of_divisors(num1);
    int sum2 = sum_of_divisors(num2);

    if(sum1 == sum2) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int num1, num2;
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);

    if(check_sum_of_divisors(num1, num2)) {
        printf("Sum of divisors are same.\n");
    } else {
        printf("Sum of divisors are not same.\n");
    }

    return 0;
}