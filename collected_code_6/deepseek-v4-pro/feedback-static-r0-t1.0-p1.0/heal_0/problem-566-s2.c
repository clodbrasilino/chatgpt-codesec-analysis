#include <stdio.h>

unsigned long long sum_of_digits(unsigned long long num) {
    unsigned long long sum = 0;
    
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    
    return sum;
}

int main(void) {
    unsigned long long number;
    
    printf("Enter a non-negative integer: ");
    if (scanf("%llu", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    
    printf("Sum of digits: %llu\n", sum_of_digits(number));
    
    return 0;
}