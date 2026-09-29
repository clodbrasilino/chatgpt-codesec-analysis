#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

uint64_t calculate_mod_pow(uint64_t base, uint64_t exponent, uint64_t modulus) {
    if (modulus <= 1) {
        return 0;
    }
    
    uint64_t result = 1;
    base = base % modulus;
    
    while (exponent > 0) {
        if ((exponent & 1) == 1) {
            result = (result * base) % modulus;
        }
        exponent >>= 1;
        base = (base * base) % modulus;
    }
    
    return result;
}

int32_t find_nth_digit(int32_t numerator, int32_t denominator, int32_t n) {
    if (denominator == 0 || n <= 0) {
        return -1;
    }

    uint64_t u_num = (uint64_t)llabs((long long)numerator);
    uint64_t u_den = (uint64_t)llabs((long long)denominator);
    uint64_t u_n = (uint64_t)n;

    u_num = u_num % u_den;
    if (u_num == 0) {
        return 0;
    }

    uint64_t remainder_factor = calculate_mod_pow(10, u_n - 1, u_den);
    uint64_t current_remainder = (u_num * remainder_factor) % u_den;
    uint32_t digit = (uint32_t)((current_remainder * 10) / u_den);

    return (int32_t)digit;
}

static int parse_int32(int32_t *out) {
    int c;
    
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && isspace(c));
    
    if (c == EOF) {
        return 0;
    }
    
    int sign = 1;
    if (c == '-') {
        sign = -1;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
    } else if (c == '+') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
    }
    
    if (!isdigit(c)) {
        if (c != EOF) {
            ungetc(c, stdin);
        }
        return 0;
    }
    
    int32_t val = 0;
    while (c != EOF && isdigit(c)) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 800000000 * 10 cannot be represented in type 'int' (AFL crash: id:000005,sig:06,src:000043,time:20638,execs:24000,op:havoc,rep:4)
         * UBSan: signed integer overflow: 1090000000 * 10 cannot be represented in type 'int' (AFL crash: id:000007,sig:06,src:000046,time:21079,execs:24475,op:havoc,rep:6)
         * UBSan: signed integer overflow: 2000000000 * 10 cannot be represented in type 'int' (AFL crash: id:000006,sig:06,src:000043,time:20766,execs:24139,op:havoc,rep:4)
         * UBSan: signed integer overflow: 1111111111 * 10 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000013,time:10787,execs:13119,op:havoc,rep:4)
         * UBSan: signed integer overflow: 1233333333 * 10 cannot be represented in type 'int' (AFL crash: id:000004,sig:06,src:000012,time:15652,execs:18468,op:havoc,rep:3)
         * UBSan: signed integer overflow: 222222222 * 10 cannot be represented in type 'int' (AFL crash: id:000009,sig:06,src:000051,time:29698,execs:33761,op:havoc,rep:6)
         * UBSan: signed integer overflow: 999999999 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:1353,execs:1606,op:havoc,rep:4)
         * UBSan: signed integer overflow: 666666666 * 10 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:4585,execs:5580,op:havoc,rep:4)
         * UBSan: signed integer overflow: 1234330000 * 10 cannot be represented in type 'int' (AFL crash: id:000008,sig:06,src:000046,time:21264,execs:24674,op:havoc,rep:5)
         */
        val = val * 10 + (c - '0');
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
    }
    
    if (c != EOF) {
        ungetc(c, stdin);
    }
    
    *out = val * sign;
    return 1;
}

static void parse_optional_slash(void) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && isspace(c));
    if (c != '/') {
        if (c != EOF) {
            ungetc(c, stdin);
        }
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000003,sig:06,src:000012,time:11000,execs:13360,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int32_t numerator;
    int32_t denominator;
    int32_t n;
    
    while (parse_int32(&numerator)) {
        parse_optional_slash();
        
        if (!parse_int32(&denominator) || !parse_int32(&n)) {
            break;
        }
        
        int32_t digit = find_nth_digit(numerator, denominator, n);
        
        if (digit >= 0) {
            printf("%" PRId32 "\n", digit);
        } else {
            printf("-1\n");
        }
    }
    
    return 0;
}