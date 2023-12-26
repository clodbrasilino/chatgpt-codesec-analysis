#include <stdio.h>

int findDifference(int number) {
    int sumEven = 0;
    int sumOdd = 0;
    
    while (number > 0) {
        int digit = number % 10;
        if (digit % 2 == 0) {
            sumEven += digit;
        } else {
            sumOdd += digit;
        }
        number /= 10;
    }
    
    return sumEven - sumOdd;
}

int main() {
    int number;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'number' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &number);
    
    int difference = findDifference(number);
    printf("Difference between sum of even and odd digits: %d\n", difference);
    
    return 0;
}