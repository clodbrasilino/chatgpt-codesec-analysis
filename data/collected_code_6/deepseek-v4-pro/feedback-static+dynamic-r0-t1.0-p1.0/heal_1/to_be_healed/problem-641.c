#include <stdio.h>
#include <stdlib.h>

int nonagonal_number(int n) {
    if (n <= 0) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1111111111 * -812156820 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:931,execs:448,op:quick,pos:10)
     * UBSan: signed integer overflow: 11111111 * 77777772 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:245,execs:138,op:havoc,rep:13)
     * UBSan: signed integer overflow: 7 * 1111111111 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:931,execs:448,op:quick,pos:10)
     */
    return n * (7 * n - 5) / 2;
}

int main(void) {
    int n;
    int result;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    result = nonagonal_number(n);
    if (result == -1) {
        printf("n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    printf("Nonagonal number %d: %d\n", n, result);
    return EXIT_SUCCESS;
}