#include <stdio.h>

long long perrin(long n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    return perrin(n - 2) + perrin(n - 3);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000001,time:42030,execs:22,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int n;
    scanf("%d", &n);
    printf("%lld\n", perrin(n));
    return 0;
}