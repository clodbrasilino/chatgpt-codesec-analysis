#include <stdio.h>
#include <stdlib.h>

int findSumOfCommonDivisors(int num1, int num2) {
    int sumOfCommonDivisors = 0;
    int minValue = (num1 < num2) ? num1 : num2;
    
    for(int i = 1; i <= minValue; ++i) {
        if(num1 % i == 0 && num2 % i == 0) {
            sumOfCommonDivisors += i;
        }
    }
    
    return sumOfCommonDivisors;
}

int main(void) {
    int num1, num2;

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);
  
    if(num1 <= 0 || num2 <= 0) {
        printf("Both inputs should be greater than 0.\n");
        return EXIT_FAILURE;
    }

    int sum = findSumOfCommonDivisors(num1, num2);

    printf("Sum of common divisors is: %d\n", sum);

    return EXIT_SUCCESS;
}
