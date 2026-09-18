#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

long derangement(long n) {
    if (n == 0) return 1;
    if (n == 1) return 0;

    int64_t* d = (int64_t*) malloc((n + 1) * sizeof(int64_t));
    if (d == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    d[0] = 1;
    d[1] = 0;
    for (long i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 20 * 939765362752547227 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:283,execs:144,op:havoc,rep:3)
         */
        int64_t next = (i - 1) * (d[i-1] + d[i-2]);
        if (next < 0 || next > INT64_MAX) {
            free(d);
            fprintf(stderr, "Overflow detected.\n");
            exit(EXIT_FAILURE);
        }
        d[i] = next;
    }
    int64_t result = d[n];
    free(d);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000001,time:1194,execs:457,op:havoc,rep:1; likely memory-safety defect
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