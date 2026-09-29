#include <stdio.h>

int checkOneBitDiff(int num1, int num2) {
    int xor = num1 ^ num2;
    return xor && !(xor & (xor - 1));
}

int main() {
    int num1 = 5, num2 = 7;
    if(checkOneBitDiff(num1, num2)) {
        printf("Numbers differ at one bit position only\n");
    } else {
        printf("Numbers do not differ at one bit position only\n");
    }
    return 0;
}