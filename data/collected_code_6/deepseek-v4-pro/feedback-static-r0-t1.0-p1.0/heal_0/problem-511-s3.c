#include <stdio.h>
#include <math.h>
#include <limits.h>

int min_sum_of_factors(int n) {
    if (n <= 0) {
        return -1;
    }
    
    int min_sum = INT_MAX;
    int sqrt_n = (int)sqrt(n);
    
    for (int i = 1; i <= sqrt_n; i++) {
        if (n % i == 0) {
            int factor1 = i;
            int factor2 = n / i;
            int current_sum = factor1 + factor2;
            if (current_sum < min_sum) {
                min_sum = current_sum;
            }
        }
    }
    
    return min_sum;
}

int main() {
    int number;
    
    printf("Enter a positive integer: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (number <= 0) {
        printf("Please enter a positive integer\n");
        return 1;
    }
    
    int result = min_sum_of_factors(number);
    printf("Minimum sum of factors: %d\n", result);
    
    return 0;
}