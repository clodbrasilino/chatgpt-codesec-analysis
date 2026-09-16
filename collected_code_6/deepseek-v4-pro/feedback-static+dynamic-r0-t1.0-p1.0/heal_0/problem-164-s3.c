#include <stdio.h>
#include <stdlib.h>

int sum_of_divisors(int n) {
    if (n <= 0) {
        return 0;
    }
    
    int sum = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int check_same_divisor_sum(int a, int b) {
    if (a <= 0 || b <= 0) {
        return 0;
    }
    
    int sum_a = sum_of_divisors(a);
    int sum_b = sum_of_divisors(b);
    
    if (sum_a < 0 || sum_b < 0) {
        return 0;
    }
    
    return sum_a == sum_b;
}

int main(void) {
    int num1 = 0;
    int num2 = 0;
    
    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (num1 <= 0 || num2 <= 0) {
        fprintf(stderr, "Numbers must be positive\n");
        return EXIT_FAILURE;
    }
    
    if (check_same_divisor_sum(num1, num2)) {
        printf("%d and %d have the same sum of divisors\n", num1, num2);
    } else {
        printf("%d and %d have different sums of divisors\n", num1, num2);
    }
    
    return EXIT_SUCCESS;
}