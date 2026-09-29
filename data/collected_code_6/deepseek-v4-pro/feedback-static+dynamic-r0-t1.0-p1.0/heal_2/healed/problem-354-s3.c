#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int safe_multiply(int a, int b) {
    if (a > 0) {
        if (b > 0) {
            if (a > INT_MAX / b) return 0;
        } else if (b < 0) {
            if (b < INT_MIN / a) return 0;
        }
    } else if (a < 0) {
        if (b > 0) {
            if (a < INT_MIN / b) return 0;
        } else if (b < 0) {
            if (a < INT_MAX / b) return 0;
        }
    }
    return 1;
}

int safe_add(int a, int b) {
    if (b > 0 && a > INT_MAX - b) return 0;
    if (b < 0 && a < INT_MIN - b) return 0;
    return 1;
}

int nth_ap_term(int first_term, int common_difference, int n) {
    int product;
    
    if (n <= 0) {
        fprintf(stderr, "Error: Term position must be positive\n");
        exit(EXIT_FAILURE);
    }
    
    if (!safe_multiply(n - 1, common_difference)) {
        fprintf(stderr, "Error: Integer overflow\n");
        exit(EXIT_FAILURE);
    }
    
    product = (n - 1) * common_difference;
    
    if (!safe_add(first_term, product)) {
        fprintf(stderr, "Error: Integer overflow\n");
        exit(EXIT_FAILURE);
    }
    
    return first_term + product;
}

int main(void) {
    int first_term, common_difference, n, result;
    
    printf("Enter first term: ");
    if (scanf("%d", &first_term) != 1) {
        fprintf(stderr, "Error: Invalid input for first term\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter common difference: ");
    if (scanf("%d", &common_difference) != 1) {
        fprintf(stderr, "Error: Invalid input for common difference\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter term position (n): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input for term position\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Error: Term position must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    result = nth_ap_term(first_term, common_difference, n);
    
    printf("The %dth term is: %d\n", n, result);
    
    return EXIT_SUCCESS;
}