#include <stdio.h>
#include <stdlib.h>

int e(int n, int k) {
    if (k == 0 || k == n) return 1;
    if (k > n) return 0;
    return e(n-1, k-1) + e(n-1, k) + e(n-1, k+1);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000002,time:358,execs:185,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int n, k;
    printf("Enter n and k: ");
    if (scanf("%d %d", &n, &k) != 2) {
        return 1;
    }
    printf("e(%d, %d) = %d\n", n, k, e(n, k));
    return 0;
}