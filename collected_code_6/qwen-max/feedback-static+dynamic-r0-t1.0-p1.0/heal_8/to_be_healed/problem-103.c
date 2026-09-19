#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 4, got <no output>
  *  test case 1 failed: expected 11, got <no output>
  *  test case 2 failed: expected 26, got <no output>
  */

int64_t eulerian_number(int n, int m) {
    if (n == 0 && m == 0)
        return 1;
    if (m >= n || n < 0 || m < 0)
        return 0;

    if (n > 63 || m > 63) {
        fprintf(stderr, "Input values are too large\n");
        exit(EXIT_FAILURE);
    }

    int64_t part1 = 0;
    int64_t part2 = 0;

    /* Possible weaknesses found:
     * UBSan: division by zero (AFL crash: id:000001,sig:06,src:000005,time:11065,execs:10724,op:havoc,rep:2)
     * ASan: FPE (AFL crash: id:000001,sig:06,src:000005,time:11065,execs:10724,op:havoc,rep:2)
     */
    if (n - m > INT64_MAX / (n - 1) || eulerian_number(n - 1, m - 1) > INT64_MAX / (n - m))
        return 0;
    part1 = (int64_t)(n - m) * eulerian_number(n - 1, m - 1);

    if (m + 1 > INT64_MAX / (n - 1) || eulerian_number(n - 1, m) > INT64_MAX / (m + 1))
        return 0;
    part2 = (int64_t)(m + 1) * eulerian_number(n - 1, m);

    if (part1 > INT64_MAX - part2 || part2 > INT64_MAX - part1 || part1 < INT64_MIN + part2 || part2 < INT64_MIN + part1) {
        fprintf(stderr, "Integer overflow detected\n");
        exit(EXIT_FAILURE);
    }

    return part1 + part2;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:9201,execs:9094,op:havoc,rep:40; likely memory-safety defect
  */

int main() {
    int n, m;
    printf("Enter values for n and m: ");
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n == 0 && m == 0) {
        printf("Eulerian number A(0, 0) is: 1\n");
        return EXIT_SUCCESS;
    }
    if (m >= n || n < 0 || m < 0) {
        printf("Eulerian number A(%d, %d) is: 0\n", n, m);
        return EXIT_SUCCESS;
    }
    int64_t result = eulerian_number(n, m);
    printf("Eulerian number A(%d, %d) is: %" PRId64 "\n", n, m, result);
    return EXIT_SUCCESS;
}