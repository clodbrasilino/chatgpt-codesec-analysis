#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long centered_hexagonal(int n) {
    if (n < 1) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4938266172841 * 2222221 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:1015,execs:470,op:havoc,rep:2)
     * UBSan: signed integer overflow: 4938270617284 * 2222222 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:1015,execs:470,op:havoc,rep:2)
     * UBSan: signed integer overflow: 123478988652100 * 11112110 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000006,time:33117,execs:14771,op:havoc,rep:8)
     * UBSan: signed integer overflow: 123479010876321 * 11112111 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000006,time:33117,execs:14771,op:havoc,rep:8)
     */
    return (long long)n * n * n - (long long)(n - 1) * (n - 1) * (n - 1);
}

int main(void) {
    char input[32];
    char *endptr;
    long val;
    int n;
    long long result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(input, &endptr, 10);
    
    if (errno != 0 || endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        return EXIT_FAILURE;
    }

    if (val < 1 || val > INT_MAX) {
        return EXIT_FAILURE;
    }

    n = (int)val;
    result = centered_hexagonal(n);
    
    if (result < 0) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);
    return EXIT_SUCCESS;
}