#include <stdio.h>

long long sum_of_cubes(int n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 668395305 * 668395305 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:281,execs:135,op:havoc,rep:5)
     *  int result is returned as long value. If the return value is long to avoid loss of information, then you have loss of information. [truncLongCastReturn]
     * UBSan: signed integer overflow: 302253 * 302253 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:1509,execs:745,op:havoc,rep:7)
     * UBSan: signed integer overflow: 468366449 * 468366450 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:281,execs:135,op:havoc,rep:5)
     */
    return (n * (n + 1) / 2) * (n * (n + 1) / 2);
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_cubes(n);
    printf("The sum of the cubes of the first %d natural numbers is: %lld\n", n, result);
    return 0;
}