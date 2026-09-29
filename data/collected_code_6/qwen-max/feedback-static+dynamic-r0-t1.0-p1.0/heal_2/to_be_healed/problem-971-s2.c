#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_segments(int n, int a, int b, int c) {
    int max = 0;
    /* Possible weaknesses found:
     *  Either the condition 'a<0' is redundant or there is division by zero at line 7. [zerodivcond]
     * ASan: FPE (AFL crash: id:000002,sig:06,src:000001,time:24118,execs:2473,op:havoc,rep:2)
     *  Division by zero
     * UBSan: division by zero (AFL crash: id:000002,sig:06,src:000001,time:24118,execs:2473,op:havoc,rep:2)
     */
    for (int i = 0; i <= n / a; ++i) {
        for (int j = 0; j <= (n - i * a) / b; ++j) {
            int k = (n - i * a - j * b);
            if (k % c == 0 && i * a + j * b + k == n) {
                if (i + j + (k / c) > max) {
                    max = i + j + (k / c);
                }
            }
        }
    }
    return max;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:8019,execs:451,op:flip1,pos:4; likely memory-safety defect
  */

int main() {
    int n, a, b, c;
    printf("Enter the total length n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input for n\n");
        return 1;
    }
    printf("Enter the segment lengths a, b, and c: ");
    /* Possible weaknesses found:
     *  Assuming that condition 'a<0' is not redundant
     */
    if (scanf("%d %d %d", &a, &b, &c) != 3 || a < 0 || b < 0 || c < 0) {
        fprintf(stderr, "Invalid input for a, b, or c\n");
        return 1;
    }

    /* Possible weaknesses found:
     *  Calling function 'max_segments', 2nd argument 'a' value is 0
     */
    int result = max_segments(n, a, b, c);
    printf("Maximum number of segments: %d\n", result);

    return 0;
}