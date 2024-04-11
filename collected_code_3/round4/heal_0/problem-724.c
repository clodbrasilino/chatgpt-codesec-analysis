#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int sumOfDigits(int base, int power) {
    int num = pow(base, power);
    int sum = 0;

    while (num != 0) {
        sum += num % 10;
        num /= 10;
    }

    return sum;
}

int main() {
    int base, power;

    printf("Enter base: ");
    scanf("%d", &base);

    printf("Enter power: ");
    scanf("%d", &power);

    printf("Sum of digits: %d\n", sumOfDigits(base, power));

    return 0;
}