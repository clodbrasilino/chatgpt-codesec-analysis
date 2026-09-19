#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 * ASan: stack-overflow (AFL crash: id:000001,sig:11,src:000002,time:380,execs:399,op:havoc,rep:1)
 */
int eulerian_number(int n, int m) {
    if (n == 0 && m == 0)
        return 1;
    if (m >= n || n < 0 || m < 0)
        return 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 2147483616 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:105,execs:127,op:havoc,rep:1)
     * UBSan: signed integer overflow: 8 * 1505621508 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000002,time:1568,execs:1554,op:havoc,rep:1)
     * UBSan: signed integer overflow: 1137586002 + 1137586002 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000002,time:1568,execs:1554,op:havoc,rep:1)
     * UBSan: signed integer overflow: 7 * -2019795292 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000002,time:1568,execs:1554,op:havoc,rep:1)
     */
    return ((n - m) * eulerian_number(n - 1, m - 1) + (m + 1) * eulerian_number(n - 1, m));
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000002,time:1010,execs:1018,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n, m;
    printf("Enter values for n and m: ");
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = eulerian_number(n, m);
    printf("Eulerian number A(%d, %d) is: %d\n", n, m, result);
    return EXIT_SUCCESS;
}