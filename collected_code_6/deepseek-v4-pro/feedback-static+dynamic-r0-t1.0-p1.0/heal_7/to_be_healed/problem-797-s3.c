#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int64_t sum_of_odd_numbers(int64_t l, int64_t r) {
    if (l > r) {
        return 0;
    }

    if (l % 2 == 0) {
        if (l == INT64_MAX) {
            return 0;
        }
        l++;
    }
    if (r % 2 == 0) {
        if (r == INT64_MIN) {
            return 0;
        }
        r--;
    }

    if (l > r) {
        return 0;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1 - -9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000004,sig:06,src:000007,time:56727,execs:17943,op:havoc,rep:2)
     */
    int64_t n = (r - l) / 2 + 1;

    if (n % 2 == 0) {
        int64_t half_n = n / 2;
        bool safe = true;

        if (half_n > 0 && l > INT64_MAX / half_n) safe = false;
        /* Possible weaknesses found:
         *  Assuming that condition 'half_n<0' is not redundant
         *  Expression 'half_n' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation. [signConversionCond]
         *  Negative value is converted to an unsigned value
         */
        else if (half_n < 0 && l < INT64_MIN / half_n) safe = false;
        if (half_n > 0 && r > INT64_MAX / half_n) safe = false;
        /* Possible weaknesses found:
         *  Expression 'half_n' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation. [signConversionCond]
         *  Negative value is converted to an unsigned value
         */
        else if (half_n < 0 && r < INT64_MIN / half_n) safe = false;

        if (safe) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2305843009213693952 * -9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000005,sig:06,src:000007,time:57407,execs:18146,op:havoc,rep:8)
             */
            int64_t term1 = half_n * l;
            int64_t term2 = half_n * r;
            if ((term1 >= 0 && term2 > INT64_MAX - term1) ||
                (term1 < 0 && term2 < INT64_MIN - term1)) {
                safe = false;
            }
        }

        if (!safe) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 1 + 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000004,time:36079,execs:11386,op:havoc,rep:24)
             */
            int64_t mid_sum = l + r;
            if ((l > 0 && r > 0 && mid_sum < 0) ||
                (l < 0 && r < 0 && mid_sum > 0)) {
                int64_t half_sum1 = l / 2;
                int64_t half_sum2 = r / 2;
                if (n > 0 && half_sum1 > INT64_MAX / n) {
                    return n * half_sum1 + n * half_sum2;
                }
                /* Possible weaknesses found:
                 *  Expression 'n' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation. [signConversionCond]
                 *  Negative value is converted to an unsigned value
                 *  Assuming that condition 'n<0' is not redundant
                 */
                if (n < 0 && half_sum1 < INT64_MIN / n) {
                    return n * half_sum1 + n * half_sum2;
                }
            }
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2305843009213693952 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000004,time:36079,execs:11386,op:havoc,rep:24)
             */
            return half_n * l + half_n * r;
        }

        int64_t sum = l + r;
        if (half_n > 0 && sum > 0 && sum > INT64_MAX / half_n) {
            return half_n * l + half_n * r;
        }
        if (half_n > 0 && sum < 0 && sum < INT64_MIN / half_n) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2305843009213693952 * -9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000005,sig:06,src:000007,time:57407,execs:18146,op:havoc,rep:8)
             */
            return half_n * l + half_n * r;
        }
        /* Possible weaknesses found:
         *  Assuming that condition 'half_n<0' is not redundant
         *  Expression 'half_n' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation. [signConversionCond]
         *  Negative value is converted to an unsigned value
         */
        if (half_n < 0 && sum > 0 && sum < INT64_MIN / half_n) {
            return half_n * l + half_n * r;
        }
        if (half_n < 0 && sum < 0 && sum > INT64_MAX / half_n) {
            return half_n * l + half_n * r;
        }

        return half_n * sum;
    } else {
        int64_t sum = l + r;
        if (sum == 0) {
            return 0;
        }
        
        int64_t half_sum = sum / 2;
        if (half_sum == 0) {
            return 0;
        }

        /* Possible weaknesses found:
         *  Assuming condition 'n>0' is true
         *  Assuming that condition 'n>0' is not redundant
         */
        if (n > 0) {
            if (half_sum > 0 && half_sum > INT64_MAX / n) {
                uint64_t un = (uint64_t)n;
                uint64_t uabs = (uint64_t)half_sum;
                uint64_t product = un * uabs;
                if (product > (uint64_t)INT64_MAX) {
                    int64_t div_l = l / 2;
                    int64_t div_r = r / 2;
                    /* Possible weaknesses found:
                     *  Condition 'n>0' is always true
                     *  Assuming condition is false
                     *  Condition 'n>0' is always true [knownConditionTrueFalse]
                     */
                    if (n > 0 && div_l > INT64_MAX / n) {
                        return n * div_l + n * div_r;
                    }
                    /* Possible weaknesses found:
                     *  Assuming that condition 'n<0' is not redundant
                     *  Condition 'n<0' is always false
                     *  Negative value is converted to an unsigned value
                     *  Condition 'n<0' is always false [knownConditionTrueFalse]
                     *  Expression 'n' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation. [signConversionCond]
                     */
                    if (n < 0 && div_l < INT64_MIN / n) {
                        return n * div_l + n * div_r;
                    }
                    /* Possible weaknesses found:
                     * UBSan: signed integer overflow: 5588893889 * 5588893888 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000006,time:51355,execs:16280,op:havoc,rep:3)
                     */
                    return n * div_l + n * div_r;
                }
            /* Possible weaknesses found:
             *  Assuming condition 'half_sum<0' is true
             */
            } else if (half_sum < 0 && half_sum < INT64_MIN / n) {
                uint64_t un = (uint64_t)n;
                /* Possible weaknesses found:
                 *  Condition 'half_sum<0' is always true
                 *  Condition 'half_sum<0' is always true [knownConditionTrueFalse]
                 */
                int64_t abs_half_sum = half_sum < 0 ? -half_sum : half_sum;
                uint64_t uabs = (uint64_t)abs_half_sum;
                uint64_t product = un * uabs;
                uint64_t max_neg = (uint64_t)INT64_MAX + 1;
                if (product > max_neg) {
                    int64_t div_l = l / 2;
                    int64_t div_r = r / 2;
                    /* Possible weaknesses found:
                     *  Condition 'n>0' is always true
                     *  Assuming condition is false
                     *  Condition 'n>0' is always true [knownConditionTrueFalse]
                     */
                    if (n > 0 && div_l > INT64_MAX / n) {
                        return n * div_l + n * div_r;
                    }
                    /* Possible weaknesses found:
                     *  Assuming that condition 'n<0' is not redundant
                     *  Condition 'n<0' is always false
                     *  Negative value is converted to an unsigned value
                     *  Condition 'n<0' is always false [knownConditionTrueFalse]
                     *  Expression 'n' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation. [signConversionCond]
                     */
                    if (n < 0 && div_l < INT64_MIN / n) {
                        return n * div_l + n * div_r;
                    }
                    return n * div_l + n * div_r;
                }
            }
        }

        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -4611686018427387903 * -4611686018427387903 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000004,sig:06,src:000007,time:56727,execs:17943,op:havoc,rep:2)
         * UBSan: signed integer overflow: 55555555561 * 55555555561 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000006,time:51749,execs:16406,op:havoc,rep:4)
         */
        return n * half_sum;
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:27378,execs:8410,op:havoc,rep:15; likely memory-safety defect
  */

int main(void) {
    int64_t l, r;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf[256];

    printf("Enter the range l and r: ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }

    buf[strcspn(buf, "\n")] = '\0';

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char format[32];
    /* Possible weaknesses found:
     * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
     */
    snprintf(format, sizeof(format), "%%" SCNd64 " %%" SCNd64, "%s");

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