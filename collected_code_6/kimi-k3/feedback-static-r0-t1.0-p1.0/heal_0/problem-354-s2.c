#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

static bool safe_add(int a, int b, int *result) {
    if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {
        return false;
    }
    *result = a + b;
    return true;
}

static bool safe_multiply(int a, int b, int *result) {
    if (a > 0) {
        if (b > 0) {
            if (a > INT_MAX / b) return false;
        } else {
            if (b < INT_MIN / a) return false;
        }
    } else {
        if (b > 0) {
            if (a < INT_MIN / b) return false;
        } else {
            if (a != 0 && b < INT_MAX / a) return false;
        }
    }
    *result = a * b;
    return true;
}

static bool calculate_nth_term(int first_term, int common_difference, int n, int *result) {
    int product;
    int sum;
    
    if (n < 1) {
        return false;
    }
    
    if (!safe_multiply(n - 1, common_difference, &product)) {
        return false;
    }
    
    if (!safe_add(first_term, product, &sum)) {
        return false;
    }
    
    *result = sum;
    return true;
}

int main(void) {
    int first_term;
    int common_difference;
    int n;
    int result;
    
    if (printf("Enter first term, common difference, and n: ") < 0) {
        return EXIT_FAILURE;
    }
    
    if (scanf("%d %d %d", &first_term, &common_difference, &n) != 3) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (!calculate_nth_term(first_term, common_difference, n, &result)) {
        (void)fprintf(stderr, "Calculation error or overflow\n");
        return EXIT_FAILURE;
    }
    
    if (printf("The %d-th term is: %d\n", n, result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}