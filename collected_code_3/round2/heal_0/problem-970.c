#include <stdio.h>

int findMin(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int num1, num2, min;

    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    min = findMin(num1, num2);

    printf("Minimum is: %d\n", min);

    return 0;
}