#include <stdio.h>

long long sum_fourth_powers(int n) {
    if (n < 0) {
        return -1;
    }
    
    long long sum = 0;
    
    for (int i = 1; i <= n; i++) {
        long long term = (long long)i * i * i * i;
        sum += term;
    }
    
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter a natural number n: ");
    
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        printf("Please enter a non-negative integer\n");
        return 1;
    }
    
    long long result = sum_fourth_powers(n);
    
    printf("Sum of fourth powers from 1 to %d = %lld\n", n, result);
    
    return 0;
}