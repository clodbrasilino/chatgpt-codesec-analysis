#include <stdio.h>
#include <stdlib.h>

long derangement(long n) {
    long d[n+1];
    d[0] = 1;
    if (n == 0) return 1;
    d[1] = 0;
    for (long i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 20 * 939765362752547227 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:37,execs:28,op:havoc,rep:4)
         * UBSan: signed integer overflow: -5784077728986054255 + -5188895624805881368 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:37,execs:28,op:havoc,rep:4)
         */
        d[i] = (i - 1) * (d[i-1] + d[i-2]);
    }
    return d[n];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000001,time:139,execs:74,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    long n;
    printf("Enter the value of n: ");
    scanf("%ld", &n);
    if (n < 0) {
        fprintf(stderr, "Value must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    long result = derangement(n);
    printf("The %ld-th Rencontres number is: %ld\n", n, result);
    return EXIT_SUCCESS;
}