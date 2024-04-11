#include <stdio.h>

int checkBitDifference(int num1, int num2) {
    int x = num1 ^ num2;
    return x && !(x & (x - 1));
}

int main() {
    int num1 = 5, num2 = 7;
    if(checkBitDifference(num1, num2)) {
        printf("The numbers differ at one bit position only\n");
    } else {
        printf("The numbers do not differ at one bit position only\n");
    }
    return 0;
}