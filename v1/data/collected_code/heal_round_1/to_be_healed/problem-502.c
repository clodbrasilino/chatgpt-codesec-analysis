#include <stdio.h>

int findRemainder(int num1, int num2) {
    int remainder = num1 % num2;
    return remainder;
}

int main() {
    int num1, num2;

    printf("Enter first number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num1' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &num1);

    printf("Enter second number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num2' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &num2);

    int remainder = findRemainder(num1, num2);
    printf("Remainder: %d\n", remainder);

    return 0;
}