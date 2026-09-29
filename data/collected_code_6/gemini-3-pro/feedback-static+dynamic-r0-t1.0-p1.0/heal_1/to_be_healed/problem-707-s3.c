#include <stdio.h>
#include <stdlib.h>

unsigned long long countSetBitsUtil(unsigned long long n) {
    if (n == 0) {
        return 0;
    }

    unsigned long long x = 0;
    while ((1ULL << x) <= n) {
        x++;
    }
    x--;

    /* Possible weaknesses found:
     * UBSan: shift exponent 18446744073709551615 is too large for 64-bit type 'unsigned long long' (AFL crash: id:000000,sig:06,src:000002,time:220,execs:125,op:havoc,rep:2)
     */
    unsigned long long bits_up_to_pow2 = x * (1ULL << (x - 1));
    unsigned long long msb_from_pow2_to_n = n - (1ULL << x) + 1;
    unsigned long long remaining_bits = countSetBitsUtil(n - (1ULL << x));

    return bits_up_to_pow2 + msb_from_pow2_to_n + remaining_bits;
}

unsigned long long countSetBits(unsigned long long n) {
    return countSetBitsUtil(n);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000002,time:233,execs:128,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    unsigned long long n;

    if (scanf("%llu", &n) != 1) {
        return EXIT_FAILURE;
    }

    unsigned long long result = countSetBits(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}