#include <stdio.h>
#include <stdlib.h>

int max_segments(int n, int a, int b, int c) {
    int max_val = 0;
    for (int i = 0; i <= n / a; ++i) {
        for (int j = 0; j <= n / b; ++j) {
            /* Possible weaknesses found:
             * ASan: FPE (AFL crash: id:000001,sig:06,src:000001,time:27387,execs:1667,op:havoc,rep:1)
             * UBSan: division by zero (AFL crash: id:000001,sig:06,src:000001,time:27387,execs:1667,op:havoc,rep:1)
             */
            for (int k = 0; k <= n / c; ++k) {
                if (a * i + b * j + c * k == n) {
                    if (i + j + k > max_val) {
                        max_val = i + j + k;
                    }
                }
            }
        }
    }
    return max_val;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:607,execs:198,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int n, a, b, c;
    printf("Enter n, a, b, c: ");
    if (scanf("%d %d %d %d", &n, &a, &b, &c) != 4) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = max_segments(n, a, b, c);
    printf("Maximum number of segments: %d\n", result);
    return EXIT_SUCCESS;
}