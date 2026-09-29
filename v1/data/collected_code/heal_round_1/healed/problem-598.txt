#include <stdio.h>
#include <math.h>

int isArmstrong(int num) {
    int originalNum, remainder, result = 0, digits = 0;

    originalNum = num;

    while (originalNum != 0) {
        originalNum /= 10;
        ++digits;
    }

    originalNum = num;

    while (originalNum != 0) {
        remainder = originalNum % 10;
        result += pow(remainder, digits);
        originalNum /= 10;
    }

    if (result == num) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int num = 0;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (isArmstrong(num)) {
        printf("%d is an Armstrong number.", num);
    } else {
        printf("%d is not an Armstrong number.", num);
    }

    return 0;
}