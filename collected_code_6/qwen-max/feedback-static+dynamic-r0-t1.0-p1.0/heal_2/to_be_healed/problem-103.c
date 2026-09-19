#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Possible weaknesses found:
 * ASan: stack-overflow (AFL crash: id:000003,sig:11,src:000002,time:16059,execs:1717,op:havoc,rep:7)
 */
int64_t eulerian_number(int n, int m) {
    if (n == 0 && m == 0)
        return 1;
    if (m >= n || n < 0 || m < 0)
        return 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 9223372036854775744 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:272,execs:268,op:havoc,rep:4)
     * UBSan: signed integer overflow: 3 * 4052533162786421527 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000002,time:8247,execs:1114,op:havoc,rep:5)
     * UBSan: signed integer overflow: 61 * 4611686018427387841 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000002,time:8247,execs:1114,op:havoc,rep:5)
     * UBSan: signed integer overflow: 468374361246528776 + 8860086939734582110 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000002,time:8247,execs:1114,op:havoc,rep:5)
     */
    return ((int64_t)(n - m) * eulerian_number(n - 1, m - 1) + (int64_t)(m + 1) * eulerian_number(n - 1, m));
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:11,src:000002,time:836,execs:765,op:havoc,rep:8; likely memory-safety defect
  */

int main() {
    int n, m;
    printf("Enter values for n and m: ");
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int64_t result = eulerian_number(n, m);
    /* Possible weaknesses found:
     *  %lld in format string (no. 3) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("Eulerian number A(%d, %d) is: %lld\n", n, m, result);
    return EXIT_SUCCESS;
}