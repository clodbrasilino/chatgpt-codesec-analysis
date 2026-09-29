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
    int result = 0, n = 0;
    for (int temp = number; temp != 0; temp /= 10) {
        ++n;
    }

    int originalNumber = number;
    long long result_long = 0;
    while (originalNumber != 0) {
        int remainder = originalNumber % 10;
        long long power = pow(remainder, n);
        if (power > INT_MAX || result_long + power > INT_MAX) return 0;
        result_long += power;
        originalNumber /= 10;
    }

    return result_long == number;
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