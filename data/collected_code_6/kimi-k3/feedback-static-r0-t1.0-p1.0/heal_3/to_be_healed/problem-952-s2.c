#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

static uint64_t power(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

static uint64_t modInverse(uint64_t n, uint64_t mod) {
    return power(n, mod - 2, mod);
}

uint64_t nCrModP(uint64_t n, uint64_t r, uint64_t p) {
    if (p <= 1) return 0;
    if (r > n) return 0;
    if (r > n - r) r = n - r;
    
    uint64_t numerator = 1;
    uint64_t denominator = 1;
    
    for (uint64_t i = 0; i < r; i++) {
        numerator = (numerator * ((n - i) % p)) % p;
        denominator = (denominator * ((i + 1) % p)) % p;
    }
    
    if (denominator == 0) return 0;
    
    return (numerator * modInverse(denominator, p)) % p;
}

int main(void) {
    uint64_t n, r, p;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char n_str[21];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char r_str[21];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char p_str[21];
    
    if (fgets(n_str, sizeof(n_str), stdin) == NULL) {
        return 1;
    }
    if (fgets(r_str, sizeof(r_str), stdin) == NULL) {
        return 1;
    }
    if (fgets(p_str, sizeof(p_str), stdin) == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(n_str, "%" SCNu64, &n) != 1) {
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(r_str, "%" SCNu64, &r) != 1) {
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(p_str, "%" SCNu64, &p) != 1) {
        return 1;
    }
    
    printf("%" PRIu64 "\n", nCrModP(n, r, p));
    
    return 0;
}