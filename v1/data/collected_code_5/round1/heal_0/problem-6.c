#include <stdio.h>
#include <stdbool.h>

bool checkOneBitDifference(int num1, int num2) {
    int xor = num1 ^ num2;
    return xor && !(xor & (xor - 1));
}

int main() {
    int num1, num2;

    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);
   
    if (checkOneBitDifference(num1, num2)) {
        printf("Numbers differ at one bit position only.\n");
    } else {
        printf("Numbers do not differ at one bit position only.\n");
    }
   
    return 0;
}