#include <stdio.h>

long long count_squares(long width, long height) {
    if (width < 0 || height < 0) return 0;
    long smaller = width < height ? width : height;
    long larger = width > height ? width : height;
    long long total = 0;
    for (long i = 1; i <= smaller; ++i)
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 6256228818753893056 + 6256088115514851789 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:260,execs:79,op:havoc,rep:9)
         */
        total += (larger - i + 1) * (smaller - i + 1);
    return total;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:7,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    long width, height;
    scanf("%ld %ld", &width, &height);
    long long result = count_squares(width, height);
    printf("%lld\n", result);
    return 0;
}