#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

/* Possible weaknesses found:
 * ASan: stack-overflow (AFL crash: id:000003,sig:11,src:000002,time:23473,execs:7476,op:havoc,rep:3)
 */
int64_t eulerian_number(int n, int m) {
    if (n == 0 && m == 0)
        return 1;
    if (m >= n || n < 0 || m < 0)
        return 0;

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 19 * 3332058336247871041 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000002,time:874,execs:823,op:havoc,rep:10)
     */
    int64_t part1 = (int64_t)(n - m) * eulerian_number(n - 1, m - 1);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3 * 4052533162786421527 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:548,execs:538,op:havoc,rep:10)
     * UBSan: signed integer overflow: 7 * 1454842842001939656 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000002,time:874,execs:823,op:havoc,rep:10)
     */
    int64_t part2 = (int64_t)(m + 1) * eulerian_number(n - 1, m);

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 - -6289144585350287035 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:548,execs:538,op:havoc,rep:10)
     * UBSan: signed integer overflow: 9223372036854775807 - -8262844179695974024 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000002,time:874,execs:823,op:havoc,rep:10)
     */
    if (part1 > INT64_MAX - part2 || part2 > INT64_MAX - part1 || part1 < INT64_MIN + part2 || part2 < INT64_MIN + part1) {
        fprintf(stderr, "Integer overflow detected\n");
        exit(EXIT_FAILURE);
    }

    return part1 + part2;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:11,src:000002,time:802,execs:758,op:havoc,rep:11; likely memory-safety defect
  */

int main() {
    int n, m;
    printf("Enter values for n and m: ");
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int64_t result = eulerian_number(n, m);
    printf("Eulerian number A(%d, %d) is: %" PRId64 "\n", n, m, result);
    return EXIT_SUCCESS;
}