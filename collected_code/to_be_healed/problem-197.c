#include <stdio.h>

int exponentiation(int base, int power) {
    int result = 1;
    for (int i = 0; i < power; i++) {
        result *= base;
    }
    return result;
}

int main() {
    int base, power;
    printf("Enter the base: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'base' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &base);
    printf("Enter the power: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'power' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &power);
    
    int result = exponentiation(base, power);
    printf("The result is: %d\n", result);
    
    return 0;
}