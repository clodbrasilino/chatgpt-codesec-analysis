#include <stdio.h>
#include <stdlib.h>

int max_segments(int n, int a, int b, int c) {
    int max = 0;
    for (int i = 0; i <= n / a; ++i) {
        for (int j = 0; j <= (n - i * a) / b; ++j) {
            /* Possible weaknesses found:
             * ASan: FPE (AFL crash: id:000001,sig:06,src:000001,time:24227,execs:3685,op:havoc,rep:14)
             * UBSan: division by zero (AFL crash: id:000001,sig:06,src:000001,time:24227,execs:3685,op:havoc,rep:14)
             */
            int k = (n - i * a - j * b) / c;
            if (i * a + j * b + k * c == n) {
                int total_segments = i + j + k;
                if (total_segments > max) {
                    max = total_segments;
                }
            }
        }
    }
    return max;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:23637,execs:3421,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int n, a, b, c;
    printf("Enter the total length n: ");
    if (scanf("%d", &n) != 1) return 1;
    printf("Enter the segment lengths a, b, c: ");
    if (scanf("%d %d %d", &a, &b, &c) != 3) return 1;

    int result = max_segments(n, a, b, c);
    printf("Maximum number of segments: %d\n", result);

    return 0;
}