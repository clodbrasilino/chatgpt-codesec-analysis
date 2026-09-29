#include <stdio.h>
#include <stdlib.h>

int checkProduct(int num) {
    int even_product = 1, odd_product = 1;
    int digit_position = 1;

    while (num != 0) {
        int digit = num % 10;
        if (digit_position % 2 == 0) {
            even_product *= digit;
        } else {
            odd_product *= digit;
        }
        num /= 10;
        digit_position++;
    }

    return even_product == odd_product;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (checkProduct(num)) {
        printf("The product of digits at even and odd places is equal.\n");
    } else {
        printf("The product of digits at even and odd places is not equal.\n");
    }

    return 0;
}