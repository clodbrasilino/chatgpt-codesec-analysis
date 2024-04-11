#include <stdio.h>
#include <math.h>

int isProductOfTwoSquares(int n) {
    int i, j;
    for(i = 0; i * i <= n; i++) {
        for(j = i; j * j <= n; j++) {
            if(i * i * j * j == n) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if(isProductOfTwoSquares(num)) {
        printf("The number can be represented as the product of two squares.\n");
    } else {
        printf("The number cannot be represented as the product of two squares.\n");
    }
    return 0;
}