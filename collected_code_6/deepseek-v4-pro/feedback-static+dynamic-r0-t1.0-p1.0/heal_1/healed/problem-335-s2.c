#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long safe_multiply(long long a, long long b, int *overflow) {
    if (a > 0 && b > 0 && a > LLONG_MAX / b) {
        *overflow = 1;
        return 0;
    }
    if (a > 0 && b < 0 && b < LLONG_MIN / a) {
        *overflow = 1;
        return 0;
    }
    if (a < 0 && b > 0 && a < LLONG_MIN / b) {
        *overflow = 1;
        return 0;
    }
    if (a < 0 && b < 0 && a < LLONG_MAX / b) {
        *overflow = 1;
        return 0;
    }
    *overflow = 0;
    return a * b;
}

long long safe_add(long long a, long long b, int *overflow) {
    if (b > 0 && a > LLONG_MAX - b) {
        *overflow = 1;
        return 0;
    }
    if (b < 0 && a < LLONG_MIN - b) {
        *overflow = 1;
        return 0;
    }
    *overflow = 0;
    return a + b;
}

long long arithmetic_progression_sum(long long first_term, long long common_difference, long long number_of_terms) {
    int overflow;
    long long result;
    
    if (number_of_terms <= 0) {
        return 0;
    }
    
    long long last_term;
    long long temp;
    
    temp = safe_multiply(number_of_terms - 1, common_difference, &overflow);
    if (overflow) {
        fprintf(stderr, "Error: Integer overflow in calculation\n");
        exit(EXIT_FAILURE);
    }
    
    last_term = safe_add(first_term, temp, &overflow);
    if (overflow) {
        fprintf(stderr, "Error: Integer overflow in calculation\n");
        exit(EXIT_FAILURE);
    }
    
    if (number_of_terms % 2 == 0) {
        long long half_terms = number_of_terms / 2;
        long long sum_ends = safe_add(first_term, last_term, &overflow);
        if (overflow) {
            fprintf(stderr, "Error: Integer overflow in calculation\n");
            exit(EXIT_FAILURE);
        }
        
        result = safe_multiply(half_terms, sum_ends, &overflow);
        if (overflow) {
            fprintf(stderr, "Error: Integer overflow in calculation\n");
            exit(EXIT_FAILURE);
        }
        return result;
    } else {
        long long sum_ends = safe_add(first_term, last_term, &overflow);
        if (overflow) {
            fprintf(stderr, "Error: Integer overflow in calculation\n");
            exit(EXIT_FAILURE);
        }
        
        long long average = sum_ends / 2;
        
        result = safe_multiply(number_of_terms, average, &overflow);
        if (overflow) {
            fprintf(stderr, "Error: Integer overflow in calculation\n");
            exit(EXIT_FAILURE);
        }
        return result;
    }
}

int main(void) {
    long long first_term, common_difference, number_of_terms;
    
    printf("Enter first term: ");
    if (scanf("%lld", &first_term) != 1) {
        fprintf(stderr, "Error: Invalid input for first term\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter common difference: ");
    if (scanf("%lld", &common_difference) != 1) {
        fprintf(stderr, "Error: Invalid input for common difference\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter number of terms: ");
    if (scanf("%lld", &number_of_terms) != 1) {
        fprintf(stderr, "Error: Invalid input for number of terms\n");
        return EXIT_FAILURE;
    }
    
    if (number_of_terms < 0) {
        fprintf(stderr, "Error: Number of terms cannot be negative\n");
        return EXIT_FAILURE;
    }
    
    long long sum = arithmetic_progression_sum(first_term, common_difference, number_of_terms);
    
    printf("Sum of arithmetic progression: %lld\n", sum);
    
    return EXIT_SUCCESS;
}