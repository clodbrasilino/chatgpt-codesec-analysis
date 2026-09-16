#include <stdio.h>
#include <math.h>

int is_armstrong(int number) {
    int original = number;
    int remainder;
    int result = 0;
    int digits = 0;

    if (number < 0) {
        return 0;
    }

    while (original != 0) {
        original /= 10;
        digits++;
    }

    original = number;

    while (original != 0) {
        remainder = original % 10;
        result += (int)pow(remainder, digits);
        original /= 10;
    }

    return result == number;
}

int main() {
    int num;

    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (is_armstrong(num)) {
        printf("%d is an Armstrong number\n", num);
    } else {
        printf("%d is not an Armstrong number\n", num);
    }

    return 0;
}