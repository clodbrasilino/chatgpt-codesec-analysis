#include <stdio.h>
#include <limits.h>

int nth_octagonal_number(int n) {
    if (n > 2107368547 || n < -2107368547) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 5528944638 * 1842981546 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:11439,execs:4852,op:havoc,rep:21)
     */
    long long temp = 3LL * n * n - 2LL * n;
    if (temp < LLONG_MIN || temp > LLONG_MAX || temp < INT_MIN || temp > INT_MAX) {
        return 0;
    }
    return (int)temp;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }
    int result = nth_octagonal_number(n);
    if (result == 0) {
        printf("Result cannot be represented as an int.\n");
        return 1;
    }
    printf("The %dth octagonal number is: %d\n", n, result);
    return 0;
}