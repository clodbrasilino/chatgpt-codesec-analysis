#include <stdio.h>

float harmonicSum(int n) {
    float sum = 0;
    for(int i = 1; i < n; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    
    float result = harmonicSum(n);
    printf("Harmonic Sum of %d: %.2f", n, result);
    
    return 0;
}