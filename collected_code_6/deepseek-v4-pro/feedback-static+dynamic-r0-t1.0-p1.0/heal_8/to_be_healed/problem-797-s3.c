#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

static int64_t safe_add(int64_t a, int64_t b, bool *overflow) {
    if ((b > 0) && (a > INT64_MAX - b)) {
        *overflow = true;
        return 0;
    }
    if ((b < 0) && (a < INT64_MIN - b)) {
        *overflow = true;
        return 0;
    }
    *overflow = false;
    return a + b;
}

static int64_t safe_mul(int64_t a, int64_t b, bool *overflow) {
    if (a == 0 || b == 0) {
        *overflow = false;
        return 0;
    }
    if (a > 0) {
        if (b > 0) {
            if (a > INT64_MAX / b) {
                *overflow = true;
                return 0;
            }
        } else {
            if (b < INT64_MIN / a) {
                *overflow = true;
                return 0;
            }
        }
    } else {
        if (b > 0) {
            if (a < INT64_MIN / b) {
                *overflow = true;
                return 0;
            }
        } else {
            if (b < INT64_MAX / a) {
                *overflow = true;
                return 0;
            }
        }
    }
    *overflow = false;
    return a * b;
}

static int64_t safe_sub(int64_t a, int64_t b, bool *overflow) {
    if ((b < 0) && (a > INT64_MAX + b)) {
        *overflow = true;
        return 0;
    }
    if ((b > 0) && (a < INT64_MIN + b)) {
        *overflow = true;
        return 0;
    }
    *overflow = false;
    return a - b;
}

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

    bool overflow = false;
    int64_t diff = safe_sub(r, l, &overflow);
    if (overflow) {
        int64_t half_l = l / 2;
        int64_t half_r = r / 2;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 177775 - -9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000013,time:11614,execs:4630,op:havoc,rep:4)
         */
        int64_t count = ((r - l) / 2) + 1;
        int64_t term1, term2;
        bool ov1 = false, ov2 = false;
        term1 = safe_mul(count, half_l, &ov1);
        term2 = safe_mul(count, half_r, &ov2);
        if (ov1 || ov2) {
            if ((l & 1) && (r & 1)) {
                if (l == INT64_MIN && r == INT64_MAX) {
                    return 0;
                }
            }
            return safe_add(term1, term2, &overflow);
        }
        return safe_add(term1, term2, &overflow);
    }

    int64_t n = diff / 2 + 1;
    /* Possible weaknesses found:
     *  Variable 'n_overflow' is assigned a value that is never used. [unreadVariable]
     */
    bool n_overflow = false;
    int64_t sum = safe_add(l, r, &overflow);
    
    if (overflow) {
        int64_t half_l = l / 2;
        int64_t half_r = r / 2;
        int64_t term1, term2;
        bool ov1 = false, ov2 = false;
        term1 = safe_mul(n, half_l, &ov1);
        term2 = safe_mul(n, half_r, &ov2);
        if (ov1 || ov2) {
            return 0;
        }
        return safe_add(term1, term2, &overflow);
    }

    if (sum == 0) {
        return 0;
    }

    int64_t half_n = n / 2;
    int64_t product;
    
    if (n % 2 == 0) {
        product = safe_mul(half_n, sum, &overflow);
        if (overflow) {
            int64_t term1, term2;
            bool ov1 = false, ov2 = false;
            term1 = safe_mul(half_n, l, &ov1);
            term2 = safe_mul(half_n, r, &ov2);
            if (ov1 || ov2) {
                return 0;
            }
            return safe_add(term1, term2, &overflow);
        }
        return product;
    } else {
        int64_t half_sum = sum / 2;
        product = safe_mul(n, half_sum, &overflow);
        if (overflow) {
            int64_t div_l = l / 2;
            int64_t div_r = r / 2;
            int64_t term1, term2;
            bool ov1 = false, ov2 = false;
            term1 = safe_mul(n, div_l, &ov1);
            term2 = safe_mul(n, div_r, &ov2);
            if (ov1 || ov2) {
                return 0;
            }
            return safe_add(term1, term2, &overflow);
        }
        return product;
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000013,time:10002,execs:4115,op:havoc,rep:1; likely memory-safety defect
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