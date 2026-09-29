#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

long long perrin(long n, long long *cache) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    if (cache[n] != -1) return cache[n];
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 6412202219048207347 + 4840428246616975367 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:12044,execs:1752,op:havoc,rep:6)
     */
    cache[n] = perrin(n - 2, cache) + perrin(n - 3, cache);
    return cache[n];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:11,src:000002,time:24201,execs:1899,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    long long *cache = (long long*)calloc(n + 1, sizeof(long long));
    if (cache == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i <= n; i++) cache[i] = -1;
    printf("%lld\n", perrin(n, cache));
    free(cache);
    return 0;
}