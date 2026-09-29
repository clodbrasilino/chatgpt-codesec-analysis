#include <stdio.h>

int countDigits(int num) {
    int count = 0;
    
    if (num == 0) {
        return 1;
    }
    
    while (num != 0) {
        num /= 10;
        count++;
    }
    
    return count;
}

int haveSameNumberOfDigits(int num1, int num2) {
    int count1 = countDigits(num1);
    int count2 = countDigits(num2);
    
    return count1 == count2;
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
    
    if (haveSameNumberOfDigits(num1, num2)) {
        printf("The numbers have the same number of digits.\n");
    } else {
        printf("The numbers do not have the same number of digits.\n");
    }
    
    return 0;
}