#include <stdio.h>

long long int sumOfFifthPowers(int n) {
    long long int sum = 0;
    
    for (int i = 1; i <= n; i++) {
        sum += (long long int)pow(i, 5);
    }
    
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    
    long long int result = sumOfFifthPowers(n);
    
    printf("Sum of fifth powers of %d natural numbers = %lld", n, result);
    
    return 0;
}