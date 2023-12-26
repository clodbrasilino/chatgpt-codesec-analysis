#include <stdio.h>

int findMinimum(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

int main() {
    int num1, num2;
    printf("Enter the first number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num1' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &num1);
    printf("Enter the second number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num2' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &num2);
    
    int minimum = findMinimum(num1, num2);
    printf("The minimum of the two numbers is: %d\n", minimum);
    
    return 0;
}