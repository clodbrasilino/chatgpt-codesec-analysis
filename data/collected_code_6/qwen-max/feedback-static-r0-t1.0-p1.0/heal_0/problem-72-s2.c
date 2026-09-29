#include <stdio.h>
#include <stdbool.h>

bool isDifferenceOfSquares(int n) {
    if (n % 4 == 0 || n % 2 != 0) {
        return true;
    }
    return false;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    if (isDifferenceOfSquares(number)) {
        printf("The number can be represented as the difference of two squares.\n");
    } else {
        printf("The number cannot be represented as the difference of two squares.\n");
    }
    return 0;
}