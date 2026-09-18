#include <stdio.h>

int maximum(int a, int b) {
    return (a > b) ? a : b;
}

int main(void) {
    int num1, num2, max;

    printf("Enter two numbers: ");
    if (scanf("%d%d", &num1, &num2) != 2) {
        printf("Invalid input!\n");
        return 0;
    }

    max = maximum(num1, num2);

    printf("The maximum of %d and %d is %d\n", num1, num2, max);

    return 0;
}