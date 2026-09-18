#include <stdio.h>
#include <math.h>

int count_factorial_digits(int n) {
    if (n < 0) {
        return 0;
    }
    if (n <= 1) {
        return 1;
    }
    double log_sum = 0.0;
    for (int i = 2; i <= n; i++) {
        log_sum += log10(i);
    }
    /* Possible weaknesses found:
     * UBSan: 2.2136e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:40292,execs:645,op:havoc,rep:8)
     */
    return (int)floor(log_sum) + 1;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    int digits = count_factorial_digits(n);
    printf("%d\n", digits);
    return 0;
}