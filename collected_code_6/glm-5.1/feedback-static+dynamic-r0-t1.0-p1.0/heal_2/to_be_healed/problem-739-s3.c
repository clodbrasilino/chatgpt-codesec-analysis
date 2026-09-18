#include <stdio.h>
#include <math.h>

long long find_smallest_triangular_index(int n) {
    if (n <= 0) {
        return -1;
    }
    if (n == 1) {
        return 3;
    }
    double min_val = pow(10, n - 1);
    double c = 2.0 * min_val;
    double k = ceil((-1.0 + sqrt(1.0 + 8.0 * c)) / 2.0);
    /* Possible weaknesses found:
     * UBSan: 2e+27 is outside the range of representable values of type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:172,execs:119,op:havoc,rep:16)
     */
    return (long long)k;
}

int main() {
    int n;
    if (scanf("%d", &n) == 1) {
        long long result = find_smallest_triangular_index(n);
        printf("%lld\n", result);
        return 0;
    }
    return 1;
}