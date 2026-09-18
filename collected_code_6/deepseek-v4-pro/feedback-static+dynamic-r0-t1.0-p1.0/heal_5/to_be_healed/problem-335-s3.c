#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

int sum_arithmetic_progression(int first_term, int common_difference, int number_of_terms) {
    /* Possible weaknesses found:
     *  Assuming that condition 'number_of_terms<=0' is not redundant
     */
    if (number_of_terms <= 0) {
        return 0;
    }
    
    long long ll_first = first_term;
    long long ll_diff = common_difference;
    /* Possible weaknesses found:
     *  ll_n is assigned 'number_of_terms' here.
     */
    long long ll_n = number_of_terms;
    
    long long last_term;
    if (ll_n > 1) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 - -1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:807,execs:572,op:havoc,rep:16)
         */
        if (ll_diff > 0 && ll_n - 1 > (LLONG_MAX - ll_first) / ll_diff) {
            return 0;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -9223372036854775808 - 1 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000006,time:2785,execs:1927,op:havoc,rep:2)
         */
        if (ll_diff < 0 && ll_n - 1 > (LLONG_MIN - ll_first) / ll_diff) {
            return 0;
        }
        last_term = ll_first + (ll_n - 1) * ll_diff;
    } else {
        last_term = ll_first;
    }
    
    long long sum;
    if (ll_n % 2 == 0) {
        long long sum_first_last;
        if ((ll_first > 0 && last_term > 0) || (ll_first < 0 && last_term < 0)) {
            if (ll_first > 0 && last_term > LLONG_MAX - ll_first) {
                return 0;
            }
            if (ll_first < 0 && last_term < LLONG_MIN - ll_first) {
                return 0;
            }
        }
        sum_first_last = ll_first + last_term;
        
        long long half_n = ll_n / 2;
        if (half_n > 0 && sum_first_last > 0 && half_n > LLONG_MAX / sum_first_last) {
            return 0;
        }
        if (half_n > 0 && sum_first_last < 0 && half_n > LLONG_MAX / (-sum_first_last)) {
            return 0;
        }
        if (half_n < 0 && sum_first_last > 0 && half_n < LLONG_MIN / sum_first_last) {
            return 0;
        }
        if (half_n < 0 && sum_first_last < 0 && half_n < LLONG_MIN / sum_first_last) {
            return 0;
        }
        sum = half_n * sum_first_last;
    } else {
        long long sum_first_last;
        if ((ll_first > 0 && last_term > 0) || (ll_first < 0 && last_term < 0)) {
            if (ll_first > 0 && last_term > LLONG_MAX - ll_first) {
                return 0;
            }
            if (ll_first < 0 && last_term < LLONG_MIN - ll_first) {
                return 0;
            }
        }
        sum_first_last = ll_first + last_term;
        
        long long half_sum = sum_first_last / 2;
        long long remainder = sum_first_last % 2;
        
        /* Possible weaknesses found:
         *  Condition 'll_n>0' is always true
         *  Assuming condition is false
         *  Condition 'll_n>0' is always true [knownConditionTrueFalse]
         */
        if (ll_n > 0 && half_sum > 0 && ll_n > LLONG_MAX / half_sum) {
            return 0;
        }
        /* Possible weaknesses found:
         *  Condition 'll_n>0' is always true
         *  Condition 'll_n>0' is always true [knownConditionTrueFalse]
         */
        if (ll_n > 0 && half_sum < 0 && ll_n > LLONG_MAX / (-half_sum)) {
            return 0;
        }
        if (ll_n < 0 && half_sum > 0 && ll_n < LLONG_MIN / half_sum) {
            return 0;
        }
        if (ll_n < 0 && half_sum < 0 && ll_n < LLONG_MIN / half_sum) {
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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000010,time:16552,execs:11266,op:havoc,rep:2; likely memory-safety defect
  */

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