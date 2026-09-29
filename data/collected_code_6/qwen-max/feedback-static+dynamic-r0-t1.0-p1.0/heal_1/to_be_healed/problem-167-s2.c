#include <stdio.h>
#include <math.h>

int find_smallest_power_of_2(int n) {
    if (n <= 0) return 1;
    int exponent = ceil(log2(n));
    /* Possible weaknesses found:
     * UBSan: left shift of 1 by 31 places cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:10605,execs:3956,op:havoc,rep:13)
     */
    return 1 << exponent;
}

int main() {
    int n;
    scanf("%d", &n);
    int result = find_smallest_power_of_2(n);
    printf("%d\n", result);
    return 0;
}