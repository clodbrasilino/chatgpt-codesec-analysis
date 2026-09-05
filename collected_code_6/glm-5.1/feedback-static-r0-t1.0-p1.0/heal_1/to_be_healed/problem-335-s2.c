#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long arithmetic_progression_sum(int a, int d, int n) {
    if (n < 0) {
        return 0;
    }
    /* Possible weaknesses found:
     *  Assuming that condition 'n==0' is not redundant
     */
    if (n == 0) {
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
    
    /* Possible weaknesses found:
     *  n_ll is assigned 'n' here.
     */
    long long n_ll = n;
    long long term_n = a + (n_ll - 1) * d;
    long long sum = n_ll * (a + term_n);
    
    if (sum % 2 != 0) {
        /* Possible weaknesses found:
         *  Condition 'n_ll>0' is always true [knownConditionTrueFalse]
         *  Condition 'n_ll>0' is always true
         */
        if (n_ll > 0 && (a + term_n) > 0) {
            if (n_ll > LLONG_MAX / (a + term_n)) {
                return 0;
            }
        /* Possible weaknesses found:
         *  Condition 'n_ll>0' is always true [knownConditionTrueFalse]
         *  Condition 'n_ll>0' is always true
         */
        } else if (n_ll > 0 && (a + term_n) < 0) {
            if (n_ll < LLONG_MIN / (a + term_n)) {
                return 0;
            }
        }
    }
    
    return sum / 2;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
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