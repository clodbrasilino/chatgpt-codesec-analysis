#include <stdio.h>

int findMinimum(int num1, int num2) {
    if(num1 < num2)
        return num1;
    else
        return num2;
}

int main() {
    int number1, number2, minimum;

    printf("Enter two numbers: ");
    scanf("%d %d", &number1, &number2);

    minimum = findMinimum(number1, number2);

    printf("Minimum is: %d\n", minimum);

    return 0;
}