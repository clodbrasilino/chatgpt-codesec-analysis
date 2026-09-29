#include <stdio.h>
#include <stdlib.h>

long long perrin(long n, long long *cache) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    if (cache[n] != -1) return cache[n];
    cache[n] = perrin(n - 2, cache) + perrin(n - 3, cache);
    return cache[n];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:10,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int n;
    scanf("%d", &n);
    /* Possible weaknesses found:
     * ASan: calloc (AFL crash: id:000002,sig:06,src:000001,time:55430,execs:1086,op:havoc,rep:2)
     */
    long long *cache = (long long*)calloc(n + 1, sizeof(long long));
    for (int i = 0; i <= n; i++) cache[i] = -1;
    printf("%lld\n", perrin(n, cache));
    free(cache);
    return 0;
}