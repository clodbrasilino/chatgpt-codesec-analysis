#include <stdio.h>

int findRemainder(int dividend, int divisor) {
    return dividend % divisor;
}

int main() {
    int num1, num2, remainder;

    printf("Enter dividend: ");
    scanf("%d", &num1);

    printf("Enter divisor: ");
    scanf("%d", &num2);

    remainder = findRemainder(num1, num2);

    printf("Remainder is: %d\n", remainder);

    return 0;
}