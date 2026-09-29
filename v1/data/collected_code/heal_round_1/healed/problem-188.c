#include <stdio.h>
#include <stdbool.h>

bool isProductOfTwoSquares(int number) {
    if (number < 0) {
        return false;
    }

    for (int i = 1; i * i <= number; i++) {
        int remaining = number / (i * i);
        if (remaining * (i * i) == number && remaining * remaining == number) {
            return true;
        }
    }
    return false;
}

int main() {
    int num = 0;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (isProductOfTwoSquares(num)) {
        printf("%d can be represented as a product of two squares\n", num);
    } else {
        printf("%d cannot be represented as a product of two squares\n", num);
    }

    return 0;
}