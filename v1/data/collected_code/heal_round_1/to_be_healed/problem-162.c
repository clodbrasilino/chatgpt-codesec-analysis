#include <stdio.h>

int sumOfPositiveIntegers(int n) {
    int sum = 0;
    int x = 0;
    
    while (n - x > 0) {
        sum += n - x;
        x += 2;
    }
    
    return sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    
    int result = sumOfPositiveIntegers(n);
    
    printf("The sum of the positive integers is: %d\n", result);
    
    return 0;
}