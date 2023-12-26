#include <stdio.h>

int findMinimum(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

int main() {
    int num1=0, num2=0;
    printf("Enter the first number: ");
    scanf("%d", &num1);
    printf("Enter the second number: ");
    scanf("%d", &num2);

    int minimum = findMinimum(num1, num2);
    printf("The minimum of the two numbers is: %d\n", minimum);

    return 0;
}