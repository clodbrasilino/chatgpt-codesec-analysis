#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

long derangement(long n) {
    if (n == 0) return 1;
    if (n == 1) return 0;

    int64_t d[n+1];
    d[0] = 1;
    d[1] = 0;
    for (long i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 20 * 939765362752547227 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000005,time:1605,execs:697,op:havoc,rep:4)
         * UBSan: signed integer overflow: -5784077728986054255 + -5188895624805881368 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000005,time:1605,execs:697,op:havoc,rep:4)
         */
        d[i] = (i - 1) * (d[i-1] + d[i-2]);
    }
    return d[n];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000005,time:1723,execs:742,op:havoc,rep:1; likely memory-safety defect
  */

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