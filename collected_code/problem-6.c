#include <stdio.h>

int diffAtOneBitPosition(int num1, int num2) {
    int xor = num1 ^ num2;
    return xor && !(xor & (xor - 1));
}

int main() {
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    
    if (diffAtOneBitPosition(num1, num2)) {
        printf("The two numbers differ at one bit position only.\n");
    } else {
        printf("The two numbers do not differ at one bit position only.\n");
    }
    
    return 0;
}