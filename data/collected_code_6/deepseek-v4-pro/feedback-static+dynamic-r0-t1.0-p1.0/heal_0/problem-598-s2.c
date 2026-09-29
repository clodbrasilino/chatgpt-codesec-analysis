#include <stdio.h>
#include <math.h>

int is_armstrong(int num) {
    int original = num;
    int sum = 0;
    int digits = 0;
    int temp = num;

    while (temp != 0) {
        digits++;
        temp /= 10;
    }

    temp = num;
    while (temp != 0) {
        int remainder = temp % 10;
        sum += (int)pow(remainder, digits);
        temp /= 10;
    }

    return sum == original;
}

int main(void) {
    int number;

    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (number < 0) {
        printf("Please enter a non-negative number\n");
        return 1;
    }

    if (is_armstrong(number)) {
        printf("%d is an Armstrong number\n", number);
    } else {
        printf("%d is not an Armstrong number\n", number);
    }

    return 0;
}