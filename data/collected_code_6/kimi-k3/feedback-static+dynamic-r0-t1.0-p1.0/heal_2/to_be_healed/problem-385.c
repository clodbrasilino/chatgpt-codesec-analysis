#include <stdio.h>
#include <stdlib.h>

long long perrin(int n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    
    long long a = 3, b = 0, c = 2;
    long long result = 0;
    
    for (int i = 3; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4840428246616975367 + 6412202219048207347 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:296,execs:158,op:havoc,rep:4)
         */
        result = a + b;
        a = b;
        b = c;
        c = result;
    }
    
    return result;
}

int main(void) {
    int n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (sscanf(buffer, "%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n < 0) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", perrin(n));
    return EXIT_SUCCESS;
}