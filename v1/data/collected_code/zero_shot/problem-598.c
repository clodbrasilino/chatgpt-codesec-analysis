#include <stdio.h>

int isArmstrong(int num) {
    int originalNum, remainder, result = 0, digits = 0;

    originalNum = num;

    // Count number of digits
    while (originalNum != 0) {
        originalNum /= 10;
        ++digits;
    }

    originalNum = num;

    // Calculate result
    while (originalNum != 0) {
        remainder = originalNum % 10;
        result += pow(remainder, digits);
        originalNum /= 10;
    }

    // Check if number is Armstrong
    if (result == num) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (isArmstrong(num)) {
        printf("%d is an Armstrong number.", num);
    } else {
        printf("%d is not an Armstrong number.", num);
    }

    return 0;
}