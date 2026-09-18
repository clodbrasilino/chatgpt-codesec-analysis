#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long sum_arithmetic_progression(long long first_term, long long common_difference, long long num_terms) {
    if (num_terms <= 0) {
        return 0;
    }
    
    if (num_terms > LLONG_MAX / 2) {
        errno = ERANGE;
        return LLONG_MAX;
    }
    
    long long twice_first;
    if (first_term > 0) {
        if (first_term > LLONG_MAX / 2) {
            errno = ERANGE;
            return LLONG_MAX;
        }
        twice_first = 2 * first_term;
    } else {
        if (first_term < LLONG_MIN / 2) {
            errno = ERANGE;
            return LLONG_MIN;
        }
        twice_first = 2 * first_term;
    }
    
    long long n_minus_one = num_terms - 1;
    long long diff_product;
    
    if (common_difference != 0 && n_minus_one != 0) {
        if (common_difference > 0) {
            if (n_minus_one > 0) {
                if (common_difference > LLONG_MAX / n_minus_one) {
                    errno = ERANGE;
                    return LLONG_MAX;
                }
            } else {
                if (common_difference > LLONG_MIN / n_minus_one) {
                    errno = ERANGE;
                    return LLONG_MIN;
                }
            }
        } else {
            if (n_minus_one > 0) {
                if (common_difference < LLONG_MIN / n_minus_one) {
                    errno = ERANGE;
                    return LLONG_MIN;
                }
            } else {
                if (n_minus_one < LLONG_MAX / common_difference) {
                    errno = ERANGE;
                    return LLONG_MAX;
                }
            }
        }
        diff_product = n_minus_one * common_difference;
    } else {
        diff_product = 0;
    }
    
    long long inner_sum;
    if (twice_first >= 0 && diff_product >= 0) {
        if (twice_first > LLONG_MAX - diff_product) {
            errno = ERANGE;
            return LLONG_MAX;
        }
        inner_sum = twice_first + diff_product;
    } else if (twice_first < 0 && diff_product < 0) {
        if (twice_first < LLONG_MIN - diff_product) {
            errno = ERANGE;
            return LLONG_MIN;
        }
        inner_sum = twice_first + diff_product;
    } else {
        inner_sum = twice_first + diff_product;
    }
    
    long long numerator;
    if (num_terms != 0 && inner_sum != 0) {
        if (num_terms > 0) {
            if (inner_sum > 0) {
                if (num_terms > LLONG_MAX / inner_sum) {
                    errno = ERANGE;
                    return LLONG_MAX;
                }
            } else {
                if (num_terms > LLONG_MIN / inner_sum) {
                    errno = ERANGE;
                    return LLONG_MIN;
                }
            }
        } else {
            if (inner_sum > 0) {
                if (num_terms < LLONG_MIN / inner_sum) {
                    errno = ERANGE;
                    return LLONG_MIN;
                }
            } else {
                if (inner_sum < LLONG_MAX / num_terms) {
                    errno = ERANGE;
                    return LLONG_MAX;
                }
            }
        }
        numerator = num_terms * inner_sum;
    } else {
        numerator = 0;
    }
    
    return numerator / 2;
}

int main(void) {
    long long first_term, common_difference, num_terms;
    
    printf("Enter first term, common difference, and number of terms: ");
    
    if (scanf("%lld %lld %lld", &first_term, &common_difference, &num_terms) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (num_terms < 0) {
        fprintf(stderr, "Number of terms cannot be negative\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    long long result = sum_arithmetic_progression(first_term, common_difference, num_terms);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Arithmetic overflow occurred\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum: %lld\n", result);
    
    return EXIT_SUCCESS;
}