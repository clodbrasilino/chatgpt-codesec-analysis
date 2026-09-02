#include <stdio.h>
#include <math.h>
#include <limits.h>

int min_sum_of_factors(int n) {
    if (n <= 0) {
        return -1;
    }
    
    int min_sum = INT_MAX;
    
    for (int i = 1; i * i <= n; i++) {
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

int main(void) {
    int test_cases[] = {1, 2, 4, 6, 12, 16, 25, 36, 100, 7, 15, 64, 1000};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int result = min_sum_of_factors(test_cases[i]);
        
        if (result == -1) {
            printf("min_sum_of_factors(%d) = Invalid input\n", test_cases[i]);
        } else {
            printf("min_sum_of_factors(%d) = %d\n", test_cases[i], result);
        }
    }
    
    int user_input = 0;
    printf("\nEnter a number to find minimum sum of factors: ");
    if (scanf("%d", &user_input) == 1) {
        int result = min_sum_of_factors(user_input);
        
        if (result == -1) {
            printf("Invalid input. Please enter a positive integer.\n");
        } else {
            printf("Minimum sum of factors for %d is: %d\n", user_input, result);
        }
    } else {
        printf("Invalid input. Please enter a valid integer.\n");
    }
    
    return 0;
}