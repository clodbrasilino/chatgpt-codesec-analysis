#include <stdio.h>
#include <math.h>
#include <limits.h>

int countDigits(int n) {
    int count = 0;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}

int isArmstrong(int num) {
    if (num < 0) {
        return 0;
    }

    int n = 0, result = 0, originalNum = num;
    while (originalNum != 0) {
        originalNum /= 10;
        n++;
    }

    originalNum = num;
    while (originalNum != 0) {
        int remainder = originalNum % 10;
        double powResult = pow(remainder, n);
        if (powResult > INT_MAX) {
            return 0;
        }
        result += (int)powResult;
        if (result > INT_MAX) {
            return 0;
        }
        originalNum /= 10;
    }

    return (result == num);
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    if (isArmstrong(number)) {
        printf("%d is an Armstrong number.\n", number);
    } else {
        printf("%d is not an Armstrong number.\n", number);
    }

    return 0;
}