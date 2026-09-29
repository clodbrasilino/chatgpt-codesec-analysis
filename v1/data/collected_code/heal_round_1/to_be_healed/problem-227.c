#include <stdio.h>

int findMinimum(int num1, int num2, int num3) {
    int min = num1;
    
    if (num2 < min) {
        min = num2;
    }
    
    if (num3 < min) {
        min = num3;
    }
    
    return min;
}

int main() {
    int num1, num2, num3;
    
    printf("Enter three numbers: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num3' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'num2' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'num1' is initialized [premium-bughuntingUninit]
     */
    scanf("%d %d %d", &num1, &num2, &num3);
    
    int minimum = findMinimum(num1, num2, num3);
    
    printf("The minimum number is: %d\n", minimum);
    
    return 0;
}