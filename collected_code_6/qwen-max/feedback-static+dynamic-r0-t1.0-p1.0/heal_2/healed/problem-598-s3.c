#include <stdio.h>
#include <math.h>
#include <limits.h>

int countDigits(int n) {
    if (n == 0) return 1;
    int count = 0;
    while (n != 0) {
        n /= 10;
        ++count;
    }
    return count;
}

int isArmstrong(int number) {
    int result = 0, n = 0, originalNumber = number;

    while (originalNumber != 0) {
        ++n;
        originalNumber /= 10;
    }

    originalNumber = number;
    while (originalNumber != 0) {
        int remainder = originalNumber % 10;
        if (remainder > 0 && INT_MAX / pow(remainder, n-1) < remainder) {
            return 0;
        }
        result += pow(remainder, n);
        originalNumber /= 10;
    }

    return result == number;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (isArmstrong(num)) {
        printf("%d is an Armstrong number.\n", num);
    } else {
        printf("%d is not an Armstrong number.\n", num);
    }

    return 0;
}