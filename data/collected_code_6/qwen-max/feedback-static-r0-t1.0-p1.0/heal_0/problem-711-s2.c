#include <stdio.h>
#include <stdbool.h>

bool isProductEqual(int num) {
    int productOdd = 1, productEven = 1;
    int place = 0;

    while (num > 0) {
        if (place % 2 == 0) {
            productEven *= num % 10;
        } else {
            productOdd *= num % 10;
        }
        num /= 10;
        place++;
    }

    return productOdd == productEven;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    if (isProductEqual(number)) {
        printf("The product of digits at even and odd places is equal.\n");
    } else {
        printf("The product of digits at even and odd places is not equal.\n");
    }

    return 0;
}