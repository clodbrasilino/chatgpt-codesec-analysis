#include <stdbool.h>
#include <math.h>
#include <stdio.h>

bool isProductOfTwoSquares(int n) {
    if (n <= 0) return false;
    for (int i = 1; i * i <= n; i++) {
        int j = n / (i * i);
        if (i * i * j == n && (int)sqrt(j) * (int)sqrt(j) == j) {
            return true;
        }
    }
    return false;
}

int main() {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (isProductOfTwoSquares(num)) {
        printf("%d can be represented as the product of two squares.\n", num);
    } else {
        printf("%d cannot be represented as the product of two squares.\n", num);
    }
    return 0;
}