#include <stdio.h>
#include <stdlib.h>

unsigned long long countSetBits(unsigned int n) {
    if (n == 0) {
        return 0;
    }

    unsigned long long total_bits = 0;
    unsigned int x = n;
    
    while (x > 0) {
        unsigned int p = 0;
        while ((1U << p) <= x) {
            p++;
        }
        p--;

        if (p == 0) {
            total_bits += 1;
            break;
        }

        total_bits += (1ULL << (p - 1)) * p + (x - (1U << p) + 1);
        x -= (1U << p);
    }
    
    return total_bits;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:847,execs:437,op:havoc,rep:8; likely memory-safety defect
  */

int main(void) {
    unsigned int n;

    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = countSetBits(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}