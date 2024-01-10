#include <stdio.h>

int findFirstDigit(int number) {
    while(number >= 10) {
        number /= 10;
    }
    return number;
}

int main() {
    int number;
    
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'number' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &number);
    
    int firstDigit = findFirstDigit(number);
    printf("First digit: %d\n", firstDigit);
    
    return 0;
}