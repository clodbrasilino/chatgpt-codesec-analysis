#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int differenceEvenOddSum(int num) {
    int sumEven = 0;
    int sumOdd = 0;
    int digit;
    
    if (num < 0) {
        num = -num;
    }
    
    while (num > 0) {
        digit = num % 10;
        if (digit % 2 == 0) {
            sumEven += digit;
        } else {
            sumOdd += digit;
        }
        num /= 10;
    }
    
    return sumEven - sumOdd;
}

int main(void) {
    int number;
    int result;
    
    printf("Enter an integer: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = differenceEvenOddSum(number);
    printf("Difference between sum of even and odd digits: %d\n", result);
    
    return EXIT_SUCCESS;
}