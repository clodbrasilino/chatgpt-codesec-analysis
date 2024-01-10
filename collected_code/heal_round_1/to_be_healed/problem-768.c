#include<stdio.h>

int checkOddParity(int num) {
    int count = 0;
    
    while (num) {
        count ^= num & 1;
        num >>= 1;
    }
    
    return count;
}

int main() {
    int number;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'number' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &number);
    
    if (checkOddParity(number)) {
        printf("Number has odd parity.");
    } else {
        printf("Number does not have odd parity.");
    }
    
    return 0;
}