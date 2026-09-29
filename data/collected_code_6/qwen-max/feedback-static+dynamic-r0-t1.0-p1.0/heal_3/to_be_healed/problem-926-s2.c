#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>

long derangement(long n) {
    if (n == 0) return 1;
    if (n == 1) return 0;

    /* Possible weaknesses found:
     * UBSan: variable length array bound evaluates to non-positive value -9223372036854775808 (AFL crash: id:000002,sig:06,src:000001,time:1056,execs:458,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000001,time:1056,execs:458,op:havoc,rep:2)
     */
    int64_t d[n+1];
    /* Possible weaknesses found:
     * ASan: dynamic-stack-buffer-overflow (AFL crash: id:000002,sig:06,src:000001,time:1056,execs:458,op:havoc,rep:2)
     */
    d[0] = 1;
    d[1] = 0;
    for (long i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 20 * 939765362752547227 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:343,execs:174,op:havoc,rep:2)
         */
        int64_t next = (i - 1) * (d[i-1] + d[i-2]);
        if (next < 0 || next > INT64_MAX) {
            fprintf(stderr, "Overflow detected.\n");
            exit(EXIT_FAILURE);
        }
        d[i] = next;
    }
    return d[n];
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1 || n < 0) {
        fprintf(stderr, "Value must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    int64_t result = derangement(n);
    printf("The %ld-th Rencontres number is: %" PRId64 "\n", n, result);
    return EXIT_SUCCESS;
}