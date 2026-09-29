#include <stdio.h>

int sum_of_digits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main(void) {
    int num;
    
    printf("Enter a non-negative integer: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (num < 0) {
        printf("Please enter a non-negative integer\n");
        return 1;
    }
    
    int result = sum_of_digits(num);
    printf("Sum of digits: %d\n", result);
    
    return 0;
}