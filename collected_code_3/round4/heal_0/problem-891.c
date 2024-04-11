#include <stdio.h>
#include <math.h>

int checkSameDigits(int num1, int num2) {
    return ((int)log10(num1) + 1) == ((int)log10(num2) + 1);
}

int main() {
    int num1, num2;
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);

    if(checkSameDigits(num1, num2)) {
        printf("Both numbers have the same number of digits.\n");
    } else {
        printf("Both numbers do not have the same number of digits.\n");
    }

    return 0;
}