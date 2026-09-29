#include <stdio.h>
#include <stdbool.h>

bool differAtOneBitPosition(unsigned int num1, unsigned int num2) {
    unsigned int xorResult = num1 ^ num2;
    return (xorResult != 0) && ((xorResult & (xorResult - 1)) == 0);
}

int main() {
    unsigned int a = 10; // 0b1010 in binary
    unsigned int b = 12; // 0b1100 in binary

    if (differAtOneBitPosition(a, b)) {
        printf("The numbers differ at exactly one bit position.\n");
    } else {
        printf("The numbers do not differ at exactly one bit position.\n");
    }

    return 0;
}