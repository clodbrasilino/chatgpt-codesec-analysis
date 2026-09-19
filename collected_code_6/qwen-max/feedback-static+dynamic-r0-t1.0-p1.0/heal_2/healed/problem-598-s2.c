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
    int n = 0, result = 0;
    for (int originalNum = num; originalNum != 0; originalNum /= 10) {
        n++;
    }

    for (int originalNum = num; originalNum != 0; originalNum /= 10) {
        int remainder = originalNum % 10;
        if (remainder > 1 && n > 31 / log10(remainder)) {
            return 0;
        }
        result += pow(remainder, n);
        if (result > INT_MAX) {
            return 0;
        }
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