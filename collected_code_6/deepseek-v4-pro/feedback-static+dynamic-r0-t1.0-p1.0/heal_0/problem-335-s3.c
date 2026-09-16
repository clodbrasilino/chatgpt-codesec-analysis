#include <stdio.h>
#include <stdlib.h>

int sum_arithmetic_progression(int first_term, int common_difference, int number_of_terms) {
    if (number_of_terms <= 0) {
        return 0;
    }
    
    if (common_difference == 0) {
        return first_term * number_of_terms;
    }
    
    int last_term = first_term + (number_of_terms - 1) * common_difference;
    long long sum = (long long)number_of_terms * (first_term + last_term) / 2;
    
    if (sum > 2147483647LL || sum < -2147483648LL) {
        return 0;
    }
    
    return (int)sum;
}

int main(void) {
    int a1, d, n;
    int result;
    
    printf("Enter first term: ");
    if (scanf("%d", &a1) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter common difference: ");
    if (scanf("%d", &d) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter number of terms: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        fprintf(stderr, "Error: Number of terms must be positive\n");
        return EXIT_FAILURE;
    }
    
    result = sum_arithmetic_progression(a1, d, n);
    printf("Sum of arithmetic progression: %d\n", result);
    
    return EXIT_SUCCESS;
}