#include <stdio.h>

int sum_even_factors(int n) {
    if (n <= 0) {
        return 0;
    }
    int sum = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i % 2 == 0) {
                sum += i;
            }
            int j = n / i;
            if (j != i) {
                if (j % 2 == 0) {
                    /* Possible weaknesses found:
                     * UBSan: signed integer overflow: 1842981548 + 614327182 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000003,time:3316,execs:2127,op:havoc,rep:13)
                     * UBSan: signed integer overflow: 1874919414 + 312486568 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:2869,execs:1836,op:havoc,rep:10)
                     * UBSan: signed integer overflow: 1617003698 + 808501848 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:1037,execs:688,op:havoc,rep:6)
                     */
                    sum += j;
                }
            }
        }
    }
    return sum;
}

int main() {
    int num;
    if (scanf("%d", &num) != 1) {
        return 1;
    }
    printf("%d\n", sum_even_factors(num));
    return 0;
}