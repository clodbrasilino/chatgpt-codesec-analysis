#include <stdio.h>
#include <math.h>

int isProductOfSquares(int num) {
    int i, j;
    for(i = 0; i * i <= num; i++) {
        for(j = i; j * j <= num; j++) {
            if(i * i * j * j == num) {
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
    if(isProductOfSquares(num)) {
        printf("The number can be represented by the product of two squares.\n");
    } else {
        printf("The number cannot be represented by the product of two squares.\n");
    }
    return 0;
}