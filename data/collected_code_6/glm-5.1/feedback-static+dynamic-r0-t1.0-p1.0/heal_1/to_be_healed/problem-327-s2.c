#include <stdio.h>
#include <stdlib.h>

int is_isosceles(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1666666666 + 1666667666 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000006,time:57194,execs:35659,op:havoc,rep:4)
     */
    if (a + b <= c || a + c <= b || b + c <= a) {
        return 0;
    }
    if (a == b || b == c || a == c) {
        return 1;
    }
    return 0;
}

int main(void) {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        return EXIT_FAILURE;
    }
    if (is_isosceles(a, b, c)) {
        printf("Isosceles\n");
    } else {
        printf("Not Isosceles\n");
    }
    return EXIT_SUCCESS;
}