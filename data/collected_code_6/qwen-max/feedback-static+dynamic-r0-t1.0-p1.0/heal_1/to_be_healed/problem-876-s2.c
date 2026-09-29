#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 142419449 * 1199545584 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:7,execs:15,op:(null),pos:0)
     */
    return (a / gcd(a, b)) * b;
}

int main() {
    int x, y;
    printf("Enter two positive integers: ");
    scanf("%d %d", &x, &y);
    if (x > 0 && y > 0) {
        printf("LCM of %d and %d is %d\n", x, y, lcm(x, y));
    } else {
        printf("Please enter positive integers.\n");
    }
    return 0;
}