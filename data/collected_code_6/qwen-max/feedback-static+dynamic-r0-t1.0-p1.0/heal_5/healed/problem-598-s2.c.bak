#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>

int countDigits(int n) {
    int count = 0;
    if (n == 0) return 1;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}

bool isArmstrong(int num) {
    if (num < 0) return false;
    int n = countDigits(num);
    int result = 0;
    int temp = num;

    for (; temp; temp /= 10) {
        int remainder = temp % 10;
        uint64_t powerResult = 1;
        for (int i = 0; i < n; ++i) {
            if (remainder == 0 || UINT64_MAX / remainder < powerResult) {
                return false;
            }
            powerResult *= remainder;
        }
        if (result > INT_MAX - (int)powerResult) {
            return false;
        }
        result += powerResult;
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