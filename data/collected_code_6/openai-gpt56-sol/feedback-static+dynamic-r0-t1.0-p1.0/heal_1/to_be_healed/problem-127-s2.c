#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int multiply_int32(int32_t lhs, int32_t rhs, int32_t *result)
{
    int64_t multiplicand = lhs;
    uint64_t multiplier;
    int64_t product = 0;

    if (result == NULL) {
        return 0;
    }

    if (rhs < 0) {
        multiplicand = -multiplicand;
        multiplier = (uint64_t)(-(int64_t)rhs);
    } else {
        multiplier = (uint64_t)rhs;
    }

    while (multiplier != 0U) {
        if ((multiplier & UINT64_C(1)) != 0U) {
            product += multiplicand;
        }
        multiplier >>= 1U;
        if (multiplier != 0U) {
            /* Possible weaknesses found:
             * UBSan: left shift of negative value -4 (AFL crash: id:000001,sig:06,src:000003,time:1208,execs:647,op:havoc,rep:2)
             * UBSan: left shift of negative value -846706916 (AFL crash: id:000002,sig:06,src:000003,time:5202,execs:2782,op:havoc,rep:2)
             * UBSan: left shift of negative value -1 (AFL crash: id:000000,sig:06,src:000003,time:579,execs:312,op:havoc,rep:1)
             */
            multiplicand <<= 1U;
        }
    }

    if (product < INT32_MIN || product > INT32_MAX) {
        return 0;
    }

    *result = (int32_t)product;
    return 1;
}

int main(void)
{
    int32_t lhs;
    int32_t rhs;
    int32_t result;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd32 " %" SCNd32, &lhs, &rhs) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!multiply_int32(lhs, rhs, &result)) {
        fputs("Multiplication overflow\n", stderr);
        return 1;
    }

    printf("%" PRId32 "\n", result);
    return 0;
}