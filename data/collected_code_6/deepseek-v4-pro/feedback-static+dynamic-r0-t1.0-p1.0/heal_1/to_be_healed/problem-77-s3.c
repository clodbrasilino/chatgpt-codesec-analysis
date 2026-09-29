#include <stdio.h>
#include <stdlib.h>

int differenceEvenOddSum(int number) {
    int evenSum = 0;
    int oddSum = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'digit' can be reduced. [variableScope]
     */
    int digit;
    
    if (number < 0) {
        number = abs(number);
    }
    
    while (number > 0) {
        digit = number % 10;
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
    int testNumbers[] = {12345, 24680, 13579, 0, -12345};
    int numTests = sizeof(testNumbers) / sizeof(testNumbers[0]);
    int i;
    
    for (i = 0; i < numTests; i++) {
        int result = differenceEvenOddSum(testNumbers[i]);
        printf("Number: %d, Difference (even - odd): %d\n", testNumbers[i], result);
    }
    
    return 0;
}