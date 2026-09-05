#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long arithmetic_progression_sum(int a, int d, int n) {
    if (n <= 0) {
        return 0;
    }
    
    if (a > 0 && d > 0) {
        if (a > LLONG_MAX - d) {
            return 0;
        }
    } else if (a < 0 && d < 0) {
        if (a < LLONG_MIN - d) {
            return 0;
        }
    }
    
    long long n_ll = n;
    long long a_ll = a;
    long long d_ll = d;
    
    long long term_n = a_ll + (n_ll - 1) * d_ll;
    long long sum_div_2 = 0;
    
    if (n_ll % 2 == 0) {
        long long a_plus_term_n = a_ll + term_n;
        if (a_plus_term_n % 2 == 0) {
            if (a_plus_term_n / 2 > LLONG_MAX / n_ll || a_plus_term_n / 2 < LLONG_MIN / n_ll) {
                return 0;
            }
            sum_div_2 = (a_plus_term_n / 2) * n_ll;
        } else {
            if (n_ll / 2 > LLONG_MAX / a_plus_term_n || n_ll / 2 < LLONG_MIN / a_plus_term_n) {
                return 0;
            }
            sum_div_2 = (n_ll / 2) * a_plus_term_n;
        }
    } else {
        long long a_plus_term_n = a_ll + term_n;
        if (n_ll > LLONG_MAX / a_plus_term_n || n_ll < LLONG_MIN / a_plus_term_n) {
            return 0;
        }
        sum_div_2 = (n_ll * a_plus_term_n) / 2;
    }
    
    return sum_div_2;
}

int main(int argc, char * const * const argv) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }
    
    char *endptr1, *endptr2, *endptr3;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    long val3 = strtol(argv[3], &endptr3, 10);
    
    if (*endptr1 != '\0' || *endptr2 != '\0' || *endptr3 != '\0') {
        return EXIT_FAILURE;
    }
    if (val1 < INT_MIN || val1 > INT_MAX || val2 < INT_MIN || val2 > INT_MAX || val3 < INT_MIN || val3 > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    int a = (int)val1;
    int d = (int)val2;
    int n = (int)val3;
    
    long long result = arithmetic_progression_sum(a, d, n);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}