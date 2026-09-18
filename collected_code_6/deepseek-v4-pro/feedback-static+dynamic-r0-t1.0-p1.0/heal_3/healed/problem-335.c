#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

long long sum_arithmetic_progression(long long first_term, long long common_difference, long long num_terms) {
    if (num_terms <= 0) {
        return 0;
    }

    if (common_difference == 0) {
        if (first_term > 0 && num_terms > LLONG_MAX / first_term) {
            return LLONG_MAX;
        }
        if (first_term < 0) {
            unsigned long long abs_first = (unsigned long long)(-(first_term + 1)) + 1;
            if (num_terms > LLONG_MAX / (long long)abs_first) {
                return LLONG_MIN;
            }
            if (abs_first > (unsigned long long)LLONG_MAX / (unsigned long long)num_terms) {
                return LLONG_MIN;
            }
        }
        return first_term * num_terms;
    }

    if (num_terms == 1) {
        return first_term;
    }

    if (common_difference > 0) {
        if (num_terms > 1) {
            if (common_difference > LLONG_MAX / (num_terms - 1)) {
                return LLONG_MAX;
            }
            long long delta = (num_terms - 1) * common_difference;
            if (first_term > LLONG_MAX - delta) {
                return LLONG_MAX;
            }
        }
    } else {
        if (num_terms > 1) {
            if (common_difference < LLONG_MIN / (num_terms - 1)) {
                return LLONG_MIN;
            }
            long long delta = (num_terms - 1) * common_difference;
            if (first_term < LLONG_MIN - delta) {
                return LLONG_MIN;
            }
        }
    }

    long long last_term;
    if (num_terms > 1) {
        long long delta = (num_terms - 1) * common_difference;
        if ((common_difference > 0 && first_term > LLONG_MAX - delta) ||
            (common_difference < 0 && first_term < LLONG_MIN - delta)) {
            return (common_difference > 0) ? LLONG_MAX : LLONG_MIN;
        }
        last_term = first_term + delta;
    } else {
        last_term = first_term;
    }

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
            if (pair_sum == LLONG_MIN && half_n > 1) {
                return LLONG_MIN;
            }
            if (half_n > LLONG_MAX / (-pair_sum)) {
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

        if (pair_sum % 2 != 0) {
            if (num_terms > LLONG_MAX / pair_sum) {
                return (pair_sum > 0) ? LLONG_MAX : LLONG_MIN;
            }
            if (num_terms < LLONG_MIN / pair_sum) {
                return (pair_sum > 0) ? LLONG_MAX : LLONG_MIN;
            }
            long long product = num_terms * pair_sum;
            if (product % 2 != 0) {
                return (product > 0) ? LLONG_MAX : LLONG_MIN;
            }
            return product / 2;
        }

        long long half_sum = pair_sum / 2;

        if (half_sum > 0 && num_terms > LLONG_MAX / half_sum) {
            return LLONG_MAX;
        }
        if (half_sum < 0 && half_sum == LLONG_MIN && num_terms > 1) {
            return LLONG_MIN;
        }
        if (half_sum < 0 && half_sum != LLONG_MIN && num_terms > LLONG_MAX / (-half_sum)) {
            return LLONG_MIN;
        }
        if (half_sum < 0 && (-half_sum) > LLONG_MAX / num_terms) {
            return LLONG_MIN;
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