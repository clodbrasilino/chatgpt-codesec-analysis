#include <stdio.h>

int isEvenProduct(int a, int b) {
    int product = a * b;
    if(product % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    if(isEvenProduct(num1, num2)) {
        printf("Product is even\n");
    } else {
        printf("Product is odd\n");
    }
    return 0;
}