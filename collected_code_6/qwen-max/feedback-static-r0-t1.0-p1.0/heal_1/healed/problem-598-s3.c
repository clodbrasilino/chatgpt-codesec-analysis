#include <stdio.h>
#include <math.h>

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
    int temp = number;

    for (; temp != 0; temp /= 10) {
        ++n;
    }

    temp = number;
    while (temp != 0) {
        int remainder = temp % 10;
        result += pow(remainder, n);
        temp /= 10;
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