#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int64_t eulerian_number(int n, int m) {
    if (n == 0 && m == 0)
        return 1;
    if (m >= n || n < 0 || m < 0)
        return 0;

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 22 * 1369410928058096062 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000003,time:6897,execs:5727,op:havoc,rep:3)
     */
    int64_t part1 = (int64_t)(n - m) * eulerian_number(n - 1, m - 1);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4 * 4591921534898186048 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000003,time:304,execs:317,op:havoc,rep:1)
     * UBSan: signed integer overflow: 6 * 3332058336247871041 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000003,time:6897,execs:5727,op:havoc,rep:3)
     */
    int64_t part2 = (int64_t)(m + 1) * eulerian_number(n - 1, m);

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 - -2854813135325378836 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000003,time:6897,execs:5727,op:havoc,rep:3)
     * UBSan: signed integer overflow: 9223372036854775807 - -79057934116807424 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:304,execs:317,op:havoc,rep:1)
     */
    if (part1 > INT64_MAX - part2) {
        fprintf(stderr, "Integer overflow detected\n");
        exit(EXIT_FAILURE);
    }

    return part1 + part2;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000003,time:166,execs:177,op:havoc,rep:8; likely memory-safety defect
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