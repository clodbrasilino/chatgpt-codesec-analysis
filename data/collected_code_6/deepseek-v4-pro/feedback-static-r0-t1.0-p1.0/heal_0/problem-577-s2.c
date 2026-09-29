#include <stdio.h>

int last_digit_factorial(int n) {
    if (n < 0)
        return -1;
    if (n == 0 || n == 1)
        return 1;
    if (n >= 5)
        return 0;
    
    int fact = 1;
    for (int i = 2; i <= n; i++) {
        fact *= i;
    }
    return fact % 10;
}

int main(void) {
    int num;
    
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    int result = last_digit_factorial(num);
    
    if (result == -1) {
        printf("Factorial is not defined for negative numbers\n");
        return 1;
    }
    
    printf("Last digit of %d! is: %d\n", num, result);
    
    return 0;
}