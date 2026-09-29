#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t octagonal_number(int64_t n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:262,execs:140,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775807 * 9223372036854775803 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:262,execs:140,op:havoc,rep:1)
     * UBSan: signed integer overflow: 55555555555 * 166666666663 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:296,execs:155,op:havoc,rep:1)
     */
    return n * (3 * n - 2);
}

int main(void) {
    int64_t n;
    
    if (scanf("%" SCNd64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    printf("%" PRId64 "\n", octagonal_number(n));
    
    return EXIT_SUCCESS;
}