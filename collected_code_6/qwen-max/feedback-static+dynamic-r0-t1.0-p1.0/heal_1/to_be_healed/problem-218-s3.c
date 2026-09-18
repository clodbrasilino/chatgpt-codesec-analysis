#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int minOpsToMakeEqual(int x, int y) {
    int g = gcd(x, y);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1873118656 + 468366441 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000007,time:8197,execs:3180,op:havoc,rep:1)
     * UBSan: division by zero (AFL crash: id:000001,sig:06,src:000004,time:16270,execs:6329,op:havoc,rep:1)
     * ASan: FPE (AFL crash: id:000001,sig:06,src:000004,time:16270,execs:6329,op:havoc,rep:1)
     */
    return (x / g - 1) + (y / g - 1);
}

int main() {
    int x, y;
    printf("Enter two numbers: ");
    if (scanf("%d %d", &x, &y) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = minOpsToMakeEqual(x, y);
    printf("Minimum operations required: %d\n", result);
    return EXIT_SUCCESS;
}