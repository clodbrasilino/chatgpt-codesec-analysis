#include <stdio.h>
#include <stdlib.h>

int digitDistance(int num1, int num2) {
    int distance = 0;
    while (num1 > 0 || num2 > 0) {
        distance += abs((num1 % 10) - (num2 % 10));
        num1 /= 10;
        num2 /= 10;
    }
    return distance;
}

int main() {
    int num1, num2;
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);
    printf("Digit distance: %d\n", digitDistance(num1, num2));
    return 0;
}