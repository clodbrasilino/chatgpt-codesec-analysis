#include <stdio.h>

int nth_octagonal_number(int n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 189347156 * 1494771484 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:761,execs:347,op:quick,pos:11)
     * UBSan: signed integer overflow: 2 * 1494771484 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:761,execs:347,op:quick,pos:11)
     * UBSan: signed integer overflow: 3 * 1494771484 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:761,execs:347,op:quick,pos:11)
     * UBSan: signed integer overflow: 460745385 * 153581795 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:368,execs:179,op:havoc,rep:2)
     */
    return 3 * n * n - 2 * n;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    if (n <= 0) {
        return 1;
    }
    int result = nth_octagonal_number(n);
    printf("The %dth octagonal number is: %d\n", n, result);
    return 0;
}