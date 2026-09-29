#include <stdio.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int num1 = 0, num2 = 0;
    printf("Enter the first number: ");
    scanf("%d", &num1);
    printf("Enter the second number: ");
    scanf("%d", &num2);
    int minimum = min(num1, num2);
    printf("Minimum number is: %d\n", minimum);
    return 0;
}