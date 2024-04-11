#include <stdio.h>

int addNumbers(int a, int b);

int multiplyNumbers(int a, int b);

int main() {
    int num1 = 5, num2 = 10, sum, product;

    sum = addNumbers(num1, num2);
    product = multiplyNumbers(num1, num2);

    printf("Sum = %d\n", sum);
    printf("Product = %d\n", product);

    return 0;
}

int addNumbers(int a, int b) {
    return a + b;
}

int multiplyNumbers(int a, int b) {
    return a * b;
}