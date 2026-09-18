#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

int sum_arithmetic_progression(int first_term, int common_difference, int number_of_terms) {
    if (number_of_terms <= 0) {
        return 0;
    }
    
    long long ll_first = first_term;
    long long ll_diff = common_difference;
    long long ll_n = number_of_terms;
    
    long long last_term;
    if (ll_n == 1) {
        last_term = ll_first;
    } else {
        if (ll_diff > 0) {
            if (ll_first > LLONG_MAX - (ll_n - 1) * ll_diff) {
                return 0;
            }
        } else if (ll_diff < 0) {
            if (ll_first < LLONG_MIN - (ll_n - 1) * ll_diff) {
                return 0;
            }
        }
        last_term = ll_first + (ll_n - 1) * ll_diff;
    }
    
    long long sum;
    long long sum_first_last;
    
    if ((ll_first > 0 && last_term > 0 && ll_first > LLONG_MAX - last_term) ||
        (ll_first < 0 && last_term < 0 && ll_first < LLONG_MIN - last_term)) {
        return 0;
    }
    sum_first_last = ll_first + last_term;
    
    if (ll_n % 2 == 0) {
        long long half_n = ll_n / 2;
        
        if (sum_first_last > 0) {
            if (half_n > LLONG_MAX / sum_first_last) {
                return 0;
            }
        } else if (sum_first_last < 0) {
            if (half_n > LLONG_MAX / (-sum_first_last)) {
                return 0;
            }
        }
        
        sum = half_n * sum_first_last;
    } else {
        long long half_sum = sum_first_last / 2;
        long long remainder = sum_first_last % 2;
        
        long long abs_half_sum = half_sum;
        if (abs_half_sum < 0) {
            abs_half_sum = -abs_half_sum;
        }
        
        if (abs_half_sum > 0 && ll_n > LLONG_MAX / abs_half_sum) {
            return 0;
        }
        
        sum = ll_n * half_sum;
        
        if (remainder != 0) {
            long long extra = (ll_n / 2) + 1;
            if (remainder > 0) {
                if (sum > LLONG_MAX - extra) {
                    return 0;
                }
                sum += extra;
            } else {
                if (sum < LLONG_MIN + extra) {
                    return 0;
                }
                sum -= extra;
            }
        }
    }
    
    if (sum > INT_MAX || sum < INT_MIN) {
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