#include <stdio.h>

int lastDigitFactorial(int num) {
    if(num < 0) {
        printf("Invalid input. Please enter a positive integer.");
        return -1;
    }

    if(num >= 5) {
        return 0;
    }

    int res[] = {1, 1, 2, 6, 4}; 

    return res[num];
}

int main() {
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    int digit = lastDigitFactorial(num);

    if(digit != -1) {
        printf("Last digit in factorial of the number: %d", digit);
    }

    return 0;
}