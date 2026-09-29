#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_of_odd_numbers(int64_t l, int64_t r) {
    if (l > r) {
        return 0;
    }

    if (l % 2 == 0) {
        l++;
    }
    if (r % 2 == 0) {
        r--;
    }

    if (l > r) {
        return 0;
    }

    int64_t n = (r - l) / 2 + 1;

    if (n % 2 == 0) {
        int64_t half_n = n / 2;
        /* Possible weaknesses found:
         *  Assuming condition 'half_n>0' is true
         */
        if (half_n > 0) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 9223372036854775807 - -7 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000004,time:52334,execs:16859,op:havoc,rep:7)
             *  Assuming condition is false
             */
            if (l > INT64_MAX - r) {
                return half_n * l + half_n * r;
            }
            int64_t sum = l + r;
            /* Possible weaknesses found:
             *  Condition 'half_n>0' is always true [knownConditionTrueFalse]
             *  Condition 'half_n>0' is always true
             */
            if (sum < 0 && half_n > 0) {
                if (sum < INT64_MIN / half_n) {
                    return half_n * l + half_n * r;
                }
            }
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 5555555555556805 * 22222222222227224 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000004,time:43463,execs:13875,op:havoc,rep:8)
             */
            return half_n * sum;
        }
        return half_n * (l + r);
    } else {
        int64_t half_sum = (l + r) / 2;
        if (half_sum == 0) {
            return 0;
        }
        if (n > 0) {
            if (half_sum > INT64_MAX / n || half_sum < INT64_MIN / n) {
                uint64_t un = (uint64_t)n;
                int64_t result_sign = 1;
                int64_t abs_half_sum = half_sum;
                if (half_sum < 0) {
                    result_sign = -1;
                    abs_half_sum = -half_sum;
                }
                uint64_t uabs = (uint64_t)abs_half_sum;
                uint64_t product = un * uabs;
                if (result_sign < 0) {
                    if (product > (uint64_t)INT64_MAX + 1) {
                        return n * half_sum;
                    }
                } else {
                    if (product > (uint64_t)INT64_MAX) {
                        return n * half_sum;
                    }
                }
            }
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 16111146035 * 16111146257 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000004,time:38968,execs:12405,op:havoc,rep:6)
         */
        return n * half_sum;
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:37948,execs:12079,op:havoc,rep:7; likely memory-safety defect
  */

int main(void) {
    int64_t l, r;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf[64];
    printf("Enter the range l and r: ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(buf, "%" SCNd64 " %" SCNd64, &l, &r) != 2) {
        printf("Invalid input\n");
        return 1;
    }

    int64_t result = sum_of_odd_numbers(l, r);
    printf("Sum of odd numbers in range [%" PRId64 ", %" PRId64 "] = %" PRId64 "\n", l, r, result);

    return 0;
}