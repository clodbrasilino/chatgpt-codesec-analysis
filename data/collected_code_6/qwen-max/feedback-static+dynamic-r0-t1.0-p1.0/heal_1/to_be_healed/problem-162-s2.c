#include <stdio.h>

int sum_series(int n) {
    int sum = 0;
    for (int i = n; i > 0; i -= 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1999999996 + 999999995 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:668,execs:291,op:havoc,rep:1)
         */
        sum += i;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);
    int result = sum_series(n);
    printf("The sum of the series is: %d\n", result);
    return 0;
}