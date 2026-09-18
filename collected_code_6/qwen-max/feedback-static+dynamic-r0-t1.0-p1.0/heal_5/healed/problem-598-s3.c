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
    if (number < 0) return 0;
    int result = 0, n = 0, originalNumber = number;

    n = countDigits(number);

    while (originalNumber != 0) {
        int remainder = originalNumber % 10;
        if (remainder > 0 && remainder > INT_MAX / pow(remainder, n - 1)) {
            return 0;
        }
        long long temp = 1;
        for (int i = 0; i < n; ++i) {
            if (temp > INT_MAX / remainder) {
                return 0;
            }
            temp *= remainder;
        }
        result += temp;
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