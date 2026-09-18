#include<stdio.h>

void swap(int *num1, int *num2) {
    int temp;

    temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

int main() {
    int number1, number2;

    printf("Enter two numbers: ");
    scanf("%d %d", &number1, &number2);

    printf("Before swapping\nNumber1 = %d\nNumber2 = %d\n", number1, number2);

    swap(&number1, &number2);

    printf("After swapping\nNumber1 = %d\nNumber2 = %d\n", number1, number2);
    
    return 0;
}