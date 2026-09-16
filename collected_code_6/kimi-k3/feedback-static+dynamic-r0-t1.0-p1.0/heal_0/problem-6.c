#include <stdio.h>
#include <stdbool.h>

bool checkOneBitDifference(unsigned int num1, unsigned int num2) {
    unsigned int xorResult = num1 ^ num2;
    return xorResult != 0 && (xorResult & (xorResult - 1)) == 0;
}

int main(void) {
    unsigned int num1, num2;
    
    if (scanf("%u %u", &num1, &num2) != 2) {
        return 1;
    }
    
    if (checkOneBitDifference(num1, num2)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}