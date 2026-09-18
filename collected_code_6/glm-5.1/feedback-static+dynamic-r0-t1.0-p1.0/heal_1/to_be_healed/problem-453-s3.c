#include <stdio.h>

int sum_even_factors(int n) {
    int sum = 0;
    if (n <= 0 || n % 2 != 0) {
        return 0;
    }
    for (int i = 2; i * i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
            int complement = n / i;
            if (complement != i && complement % 2 == 0) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 2140795574 + 9699328 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:21844,execs:11260,op:havoc,rep:7)
                 * UBSan: signed integer overflow: 2130766410 + 51969910 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:7204,execs:4105,op:havoc,rep:8)
                 * UBSan: signed integer overflow: 2100059780 + 201605736 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:57105,execs:29493,op:havoc,rep:8)
                 */
                sum += complement;
            }
        }
    }
    return sum;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    int result = sum_even_factors(n);
    printf("%d\n", result);
    return 0;
}