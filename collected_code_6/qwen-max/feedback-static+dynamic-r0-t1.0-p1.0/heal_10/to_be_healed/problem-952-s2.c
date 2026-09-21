#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t modPow(uint64_t base, uint64_t exp, uint64_t modulus) {
    uint64_t result = 1;
    base = base % modulus;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % modulus;
        }
        exp >>= 1;
        base = (base * base) % modulus;
    }
    return result;
}

uint64_t modInverse(uint64_t a, uint64_t m) {
    return modPow(a, m - 2, m);
}

uint64_t nCrModPFermat(uint64_t n, uint64_t r, uint64_t p) {
    if (r == 0 || r == n) return 1;
    if (r > n - r) r = n - r;

    uint64_t numerator = 1, denominator = 1;
    for (uint64_t i = 0; i < r; ++i) {
        numerator = (numerator * (n - i)) % p;
        denominator = (denominator * (i + 1)) % p;
    }

    return (numerator * modInverse(denominator, p)) % p;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:15867,execs:5069,op:havoc,rep:7; likely memory-safety defect
  */

int main() {
    uint64_t n, r, p;
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &n) != 1) return 1;
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &r) != 1) return 1;
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &p) != 1) return 1;
    printf("%" PRIu64 "\n", nCrModPFermat(n, r, p));
    return 0;
}