#include <stdio.h>

int nth_octagonal_number(int n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * -2052810070 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:987,execs:339,op:havoc,rep:6)
     * UBSan: signed integer overflow: -1863462914 * -2052810070 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:987,execs:339,op:havoc,rep:6)
     * UBSan: signed integer overflow: 3 * -2052810070 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:987,execs:339,op:havoc,rep:6)
     * UBSan: signed integer overflow: 448419444 * 149473148 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:314,execs:140,op:havoc,rep:13)
     * UBSan: signed integer overflow: -2117932372 - 189347156 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:987,execs:339,op:havoc,rep:6)
     */
    return 3 * n * n - 2 * n;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    int result = nth_octagonal_number(n);
    printf("The %dth octagonal number is: %d\n", n, result);
    return 0;
}