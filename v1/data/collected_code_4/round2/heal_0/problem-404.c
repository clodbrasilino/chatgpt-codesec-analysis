#include <stdio.h>

int findMinimum(int number1, int number2) {
    return (number1 < number2) ? number1 : number2;
}

int main() {
    int number1, number2, minimum;

    printf("Enter two numbers: ");
    if(scanf("%d %d", &number1, &number2) == 2) {
        minimum = findMinimum(number1, number2);
        printf("Minimum: %d\n", minimum);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}