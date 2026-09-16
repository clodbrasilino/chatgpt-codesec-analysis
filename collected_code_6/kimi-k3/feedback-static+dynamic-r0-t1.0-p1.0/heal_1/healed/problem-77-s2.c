#include <stdio.h>
#include <stdlib.h>

int findDigitDifference(int number) {
    int evenSum = 0;
    int oddSum = 0;
    
    number = abs(number);
    
    while (number != 0) {
        int digit = number % 10;
        if (digit % 2 == 0) {
            evenSum += digit;
        } else {
            oddSum += digit;
        }
        number /= 10;
    }
    
    return evenSum - oddSum;
}

int main(void) {
    int number;
    int result;
    
    printf("Enter an integer: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = findDigitDifference(number);
    printf("Difference (even sum - odd sum): %d\n", result);
    
    return EXIT_SUCCESS;
}