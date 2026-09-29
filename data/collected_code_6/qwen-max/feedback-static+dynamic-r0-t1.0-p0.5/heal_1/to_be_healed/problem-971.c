#include <stdio.h>
#include <stdlib.h>

int max_segments(int n, int a, int b, int c) {
    int max = 0;
    /* Possible weaknesses found:
     * UBSan: division by zero (AFL crash: id:000001,sig:06,src:000000,time:2282,execs:930,op:havoc,rep:14)
     * ASan: FPE (AFL crash: id:000001,sig:06,src:000000,time:2282,execs:930,op:havoc,rep:14)
     */
    for (int i = 0; i <= n / a; ++i) {
        for (int j = 0; j <= (n - i * a) / b; ++j) {
            /* Possible weaknesses found:
             * ASan: FPE (AFL crash: id:000002,sig:06,src:000000,time:56604,execs:10411,op:havoc,rep:4)
             * UBSan: division by zero (AFL crash: id:000002,sig:06,src:000000,time:56604,execs:10411,op:havoc,rep:4)
             */
            int k = (n - i * a - j * b) / c;
            if (i * a + j * b + k * c == n) {
                if (i + j + k > max) {
                    max = i + j + k;
                }
            }
        }
    }
    return max;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:1501,execs:621,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    int n, a, b, c;
    printf("Enter the total length n: ");
    scanf("%d", &n);
    printf("Enter the segment lengths a, b, and c: ");
    scanf("%d %d %d", &a, &b, &c);

    int result = max_segments(n, a, b, c);
    printf("Maximum number of segments: %d\n", result);

    return 0;
}