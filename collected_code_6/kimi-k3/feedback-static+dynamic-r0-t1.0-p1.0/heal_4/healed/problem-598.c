#include <stdio.h>
#include <math.h>
#include <limits.h>

int isArmstrong(int num) {
    int originalNum, n = 0;
    double result = 0;

    if (num < 0) {
        return 0;
    }

    originalNum = num;

    while (originalNum != 0) {
        originalNum /= 10;
        ++n;
    }

    originalNum = num;

    while (originalNum != 0) {
        int remainder = originalNum % 10;
        result += pow(remainder, n);
        originalNum /= 10;
    }

    if (result > (double)INT_MAX || result < (double)INT_MIN) {
        return 0;
    }

    if ((int)result == num)
        return 1;
    else
        return 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (isArmstrong(num))
        printf("%d is an Armstrong number.\n", num);
    else
        printf("%d is not an Armstrong number.\n", num);

    return 0;
}