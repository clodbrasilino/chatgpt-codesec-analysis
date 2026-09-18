#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_arithmetic_progression(long long first_term, long long common_difference, long long num_terms) {
    if (num_terms <= 0) {
        return 0;
    }

    if (common_difference == 0) {
        if (num_terms > 0 && (first_term > LLONG_MAX / num_terms || first_term < LLONG_MIN / num_terms)) {
            return (first_term > 0) ? LLONG_MAX : LLONG_MIN;
        }
        return first_term * num_terms;
    }

    if (num_terms == 1) {
        return first_term;
    }

    if (common_difference > 0) {
        if (first_term > LLONG_MAX - (num_terms - 1) * common_difference) {
            return LLONG_MAX;
        }
    } else {
        if (first_term < LLONG_MIN - (num_terms - 1) * common_difference) {
            return LLONG_MIN;
        }
    }

    long long last_term = first_term + (num_terms - 1) * common_difference;

    if (num_terms % 2 == 0) {
        long long half_n = num_terms / 2;
        long long pair_sum;
        
        if ((first_term > 0 && last_term > LLONG_MAX - first_term) ||
            (first_term < 0 && last_term < LLONG_MIN - first_term)) {
            if (first_term > 0 || last_term > 0) {
                return LLONG_MAX;
            } else {
                return LLONG_MIN;
            }
        }
        pair_sum = first_term + last_term;
        
        if (pair_sum > 0) {
            if (half_n > LLONG_MAX / pair_sum) {
                return LLONG_MAX;
            }
        } else if (pair_sum < 0) {
            if (half_n > LLONG_MIN / pair_sum) {
                return LLONG_MIN;
            }
        }
        
        return half_n * pair_sum;
    } else {
        long long pair_sum;
        
        if ((first_term > 0 && last_term > LLONG_MAX - first_term) ||
            (first_term < 0 && last_term < LLONG_MIN - first_term)) {
            if (first_term > 0 || last_term > 0) {
                return LLONG_MAX;
            } else {
                return LLONG_MIN;
            }
        }
        pair_sum = first_term + last_term;
        
        long long half_sum = pair_sum / 2;
        
        if (num_terms > 0) {
            if (half_sum > LLONG_MAX / num_terms || half_sum < LLONG_MIN / num_terms) {
                return (half_sum > 0) ? LLONG_MAX : LLONG_MIN;
            }
        } else {
            if (half_sum < LLONG_MAX / num_terms || half_sum > LLONG_MIN / num_terms) {
                return (half_sum > 0) ? LLONG_MAX : LLONG_MIN;
            }
        }
        
        return num_terms * half_sum;
    }
}

int main(void) {
    long long a, d, n;
    
    if (scanf("%lld %lld %lld", &a, &d, &n) != 3) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", sum_arithmetic_progression(a, d, n));
    
    return EXIT_SUCCESS;
}