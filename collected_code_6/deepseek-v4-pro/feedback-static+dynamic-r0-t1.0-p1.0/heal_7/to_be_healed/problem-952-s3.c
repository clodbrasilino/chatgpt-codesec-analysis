#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t mul_mod(int64_t a, int64_t b, int64_t mod) {
    int64_t result = 0;
    int64_t ua;
    int64_t ub;
    
    if (mod <= 0) {
        return 0;
    }
    
    ua = a % mod;
    if (ua < 0) {
        ua += mod;
    }
    ub = b % mod;
    if (ub < 0) {
        ub += mod;
    }
    
    while (ub > 0) {
        if (ub & 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2086323456135843210 + 8345293824543372840 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000026,time:59062,execs:17850,op:havoc,rep:1)
             */
            int64_t sum = result + ua;
            if (sum >= mod || sum < result) {
                sum %= mod;
                if (sum < 0) sum += mod;
            }
            result = sum;
        }
        {
            if (ua > INT64_MAX - ua) {
                ua = ua - (mod - ua);
                if (ua >= mod || ua < 0) {
                    ua %= mod;
                    if (ua < 0) ua += mod;
                }
            } else {
                ua = ua * 2;
            }
            if (ua >= mod) {
                ua %= mod;
                if (ua < 0) ua += mod;
            }
        }
        ub >>= 1;
    }
    result %= mod;
    if (result < 0) result += mod;
    return result;
}

int64_t power_mod(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    int64_t b;
    
    if (mod <= 0) {
        return 0;
    }
    
    b = base % mod;
    if (b < 0) {
        b += mod;
    }
    
    while (exp > 0) {
        if (exp & 1) {
            result = mul_mod(result, b, mod);
        }
        b = mul_mod(b, b, mod);
        exp >>= 1;
    }
    return result;
}

int64_t mod_inverse(int64_t a, int64_t p) {
    return power_mod(a, p - 2, p);
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 6, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  *  test case 1 failed: expected 11, got <no output>
  */

int64_t ncr_mod_p(int64_t n, int64_t r, int64_t p) {
    int64_t numerator;
    int64_t denominator;
    int64_t i;
    
    if (r > n || r < 0) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    
    if (r > n - r) {
        r = n - r;
    }
    
    numerator = 1;
    denominator = 1;
    
    for (i = 0; i < r; i++) {
        int64_t term1 = (n - i) % p;
        if (term1 < 0) {
            term1 += p;
        }
        int64_t term2 = (i + 1) % p;
        if (term2 < 0) {
            term2 += p;
        }
        numerator = mul_mod(numerator, term1, p);
        denominator = mul_mod(denominator, term2, p);
    }
    
    return mul_mod(numerator, mod_inverse(denominator, p), p);
}

int main(void) {
    int64_t n, r, p;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf[256];
    
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(buf, "%" SCNd64 " %" SCNd64 " %" SCNd64, &n, &r, &p) != 3) {
        return 1;
    }
    
    if (p <= 1) {
        return 1;
    }
    
    printf("%" PRId64 "\n", ncr_mod_p(n, r, p));
    
    return 0;
}