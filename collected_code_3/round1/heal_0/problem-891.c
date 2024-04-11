#include <stdio.h>
#include <math.h>

int checkDigits(int num1, int num2) {
    int count1 = 0, count2 = 0;

    while(num1 != 0) {
        num1 /= 10;
        ++count1;
    }

    while(num2 != 0) {
        num2 /= 10;
        ++count2;
    }

    if(count1 == count2)
        return 1;
    else
        return 0;
}

int main() {
    int num1, num2;

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    if(checkDigits(num1, num2))
        printf("Both numbers have the same number of digits.\n");
    else
        printf("Both numbers do not have the same number of digits.\n");

    return 0;
}