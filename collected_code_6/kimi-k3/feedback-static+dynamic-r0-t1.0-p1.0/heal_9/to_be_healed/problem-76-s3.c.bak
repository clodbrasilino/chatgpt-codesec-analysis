#include <stdio.h>

long long count_squares(int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    if (m > n) {
        int temp = m;
        m = n;
        n = temp;
    }
    long long a = m;
    long long b = n;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4255197293504270892 * 4125625913 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:1632,execs:973,op:havoc,rep:1)
     */
    return a * (a + 1) * (3 * b - a + 1) / 6;
}

int main() {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2) {
        return 1;
    }
    printf("%lld\n", count_squares(m, n));
    return 0;
}