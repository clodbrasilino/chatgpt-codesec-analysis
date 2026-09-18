#include <stdio.h>
#include <math.h>

long long find_smallest_triangular_index(int n) {
    if (n <= 0) {
        return -1;
    }
    if (n == 1) {
        return 1;
    }

    double val = pow(10, n - 1);
    double discriminant = 1 + 8 * val;
    /* Possible weaknesses found:
     * UBSan: inf is outside the range of representable values of type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:588,execs:305,op:havoc,rep:12)
     */
    long long index = (long long)ceil((-1 + sqrt(discriminant)) / 2.0);

    return index;
}

int main(void) {
    int n;

    if (scanf("%d", &n) != 1) {
        return 1;
    }

    long long index = find_smallest_triangular_index(n);

    if (index == -1) {
        return 1;
    }

    printf("%lld\n", index);

    return 0;
}