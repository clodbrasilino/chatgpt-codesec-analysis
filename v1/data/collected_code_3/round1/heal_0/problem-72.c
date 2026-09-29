#include <stdio.h>
#include <stdbool.h>

bool checkDifferenceOfSquares(int n) {
    return n % 4 != 2;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (checkDifferenceOfSquares(num)) {
        printf("The number can be represented as the difference of two squares.\n");
    } else {
        printf("The number cannot be represented as the difference of two squares.\n");
    }

    return 0;
}