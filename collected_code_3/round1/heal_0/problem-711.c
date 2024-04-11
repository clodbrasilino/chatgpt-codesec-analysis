#include <stdio.h>
#include <stdbool.h>

bool checkProduct(int num) {
    int odd_product = 1, even_product = 1, count = 0;

    while (num) {
        int digit = num % 10;
        if (count % 2 == 0)
            even_product *= digit;
        else
            odd_product *= digit;

        num /= 10;
        count++;
    }

    return odd_product == even_product;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (checkProduct(num))
        printf("The product of digits at even and odd places is equal.\n");
    else
        printf("The product of digits at even and odd places is not equal.\n");

    return 0;
}