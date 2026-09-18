#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

bool is_present_in_sequence(long long n, long long target) {
    if (target < 0) {
        return false;
    }

    unsigned long long low = 1;
    unsigned long long high;

    if (n > 1) {
        unsigned long long max_val;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:1833,execs:1204,op:havoc,rep:3)
         */
        if (n > LLONG_MAX / (n + 1)) {
            max_val = ULLONG_MAX;
        } else {
            max_val = ((unsigned long long)n * ((unsigned long long)n + 1)) / 2;
        }

        if (target > 0 && (unsigned long long)target > max_val) {
            return false;
        }

        if (max_val < ULLONG_MAX / 2) {
            high = n;
        } else {
            high = 1;
            while (high < n && high < ULLONG_MAX / (high + 1)) {
                high *= 2;
            }
            if (high > n) high = n;
            if (high < n) high = n;
        }
    } else {
        high = 1;
    }

    while (low <= high) {
        unsigned long long mid = low + (high - low) / 2;
        unsigned long long sum;

        if (mid > ULLONG_MAX / (mid + 1)) {
            sum = ULLONG_MAX;
        } else {
            sum = (mid * (mid + 1)) / 2;
        }

        if (sum == (unsigned long long)target) {
            return true;
        } else if (sum < (unsigned long long)target) {
            low = mid + 1;
        } else {
            if (mid == 0) break;
            high = mid - 1;
        }
    }

    return false;
}

int main(void) {
    long long n, target;

    printf("Enter the sequence limit (n): ");
    if (scanf("%lld", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter the number to search: ");
    if (scanf("%lld", &target) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (n < 1) {
        printf("Sequence limit must be positive\n");
        return 1;
    }

    if (is_present_in_sequence(n, target)) {
        printf("%lld is present in the sequence\n", target);
    } else {
        printf("%lld is not present in the sequence\n", target);
    }

    return 0;
}