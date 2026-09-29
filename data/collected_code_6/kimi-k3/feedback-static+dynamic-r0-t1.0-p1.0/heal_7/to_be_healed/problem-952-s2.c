#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

static uint64_t power(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (uint64_t)((__uint128_t)res * base % mod);
        base = (uint64_t)((__uint128_t)base * base % mod);
        exp >>= 1;
    }
    return res;
}

static uint64_t modInverse(uint64_t n, uint64_t mod) {
    return power(n, mod - 2, mod);
}

static uint64_t nCrModPLucas(uint64_t n, uint64_t r, uint64_t p);

static uint64_t nCrModPSmall(uint64_t n, uint64_t r, uint64_t p) {
    if (r > n) return 0;
    if (r > n - r) r = n - r;
    
    uint64_t res = 1;
    
    for (uint64_t i = 0; i < r; i++) {
        uint64_t num = (n - i) % p;
        uint64_t den = (i + 1) % p;
        
        if (den == 0) {
            uint64_t count = 0;
            uint64_t temp_n = n - i;
            uint64_t temp_r = i + 1;
            
            while (temp_n % p == 0) {
                temp_n /= p;
                count++;
            }
            while (temp_r % p == 0) {
                temp_r /= p;
                count--;
            }
            
            if (count > 0) return 0;
            
            num = temp_n % p;
            den = temp_r % p;
        }
        
        res = (uint64_t)((__uint128_t)res * num % p);
        res = (uint64_t)((__uint128_t)res * modInverse(den, p) % p);
    }
    
    return res;
}

static uint64_t nCrModPLucas(uint64_t n, uint64_t r, uint64_t p) {
    if (r > n) return 0;
    if (p == 2) {
        return ((r & ~n) == 0) ? 1 : 0;
    }
    
    uint64_t res = 1;
    /* Possible weaknesses found:
     *  Assuming that condition 'r>0' is not redundant
     *  Assuming that condition 'n>0' is not redundant
     */
    while (n > 0 || r > 0) {
        /* Possible weaknesses found:
         *  Either the condition 'n>0' is redundant or there is division by zero at line 68. [zerodivcond]
         *  Division by zero
         */
        uint64_t ni = n % p;
        /* Possible weaknesses found:
         *  Either the condition 'n>0' is redundant or there is division by zero at line 69. [zerodivcond]
         *  Division by zero
         */
        uint64_t ri = r % p;
        if (ri > ni) return 0;
        res = (uint64_t)((__uint128_t)res * nCrModPSmall(ni, ri, p) % p);
        /* Possible weaknesses found:
         *  Assignment to 'n/=p'
         *  Either the condition 'r>0' is redundant or there is division by zero at line 72. [zerodivcond]
         *  Division by zero
         */
        n /= p;
        /* Possible weaknesses found:
         *  Assignment to 'r/=p'
         */
        r /= p;
    }
    return res;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got 10
  */

uint64_t nCrModP(uint64_t n, uint64_t r, uint64_t p) {
    if (p <= 1) return 0;
    if (r > n) return 0;
    
    if (n < p) {
        return nCrModPSmall(n, r, p);
    }
    
    return nCrModPLucas(n, r, p);
}

int main(void) {
    uint64_t n, r, p;
    
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64 " %" SCNu64 " %" SCNu64, &n, &r, &p) != 3) {
        return 1;
    }
    
    printf("%" PRIu64 "\n", nCrModP(n, r, p));
    
    return 0;
}