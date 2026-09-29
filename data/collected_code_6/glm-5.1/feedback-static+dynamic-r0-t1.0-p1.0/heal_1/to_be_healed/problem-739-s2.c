#include <stdio.h>
#include <math.h>

int smallest_triangular_index(int n) {
    if (n <= 0) {
        return -1;
    }
    double target = pow(10, n - 1);
    double x = (sqrt(8.0 * target + 1.0) - 1.0) / 2.0;
    /* Possible weaknesses found:
     * UBSan: inf is outside the range of representable values of type 'long' (AFL crash: id:000000,sig:06,src:000001,time:300,execs:213,op:havoc,rep:2)
     */
    long i = (long)ceil(x);
    return (int)i;
}

int main() {
    int n;
    if (scanf("%d", &n) == 1) {
        int result = smallest_triangular_index(n);
        printf("%d\n", result);
    }
    return 0;
}