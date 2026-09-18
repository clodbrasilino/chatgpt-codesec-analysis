#include <stdio.h>
#include <math.h>
#include <limits.h>

int count_digits(int num) {
    int count = 0;
    if (num == 0) return 1;
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

int is_armstrong(int num) {
    if (num > INT_MAX || num < INT_MIN) return 0;
    int original_num = num, sum = 0, digits = count_digits(num);
    while (num > 0) {
        int digit = num % 10;
        long long temp_sum = sum + pow(digit, digits);
        if (temp_sum > INT_MAX) return 0;
        sum = temp_sum;
        num /= 10;
    }
    return sum == original_num;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    if (is_armstrong(number)) {
        printf("%d is an Armstrong number.\n", number);
    } else {
        printf("%d is not an Armstrong number.\n", number);
    }
    return 0;
}