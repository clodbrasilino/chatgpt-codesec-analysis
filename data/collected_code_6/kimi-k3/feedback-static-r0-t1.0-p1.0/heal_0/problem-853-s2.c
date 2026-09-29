#include <stdio.h>

int sum_of_odd_factors(int n) {
    int sum = 0;
    int i;
    
    if (n <= 0) {
        return 0;
    }
    
    for (i = 1; i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
        }
    }
    
    return sum;
}

int main(void) {
    int number;
    int result;
    
    printf("Enter a positive integer: ");
    
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (number <= 0) {
        fprintf(stderr, "Number must be positive\n");
        return 1;
    }
    
    result = sum_of_odd_factors(number);
    printf("Sum of odd factors of %d is %d\n", number, result);
    
    return 0;
}