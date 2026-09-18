#include <stdio.h>
#include <stdlib.h>

long long sum_of_squares(int n) {
    if (n < 1) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1562365709135569806 * -1795074731 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:2230,execs:1381,op:havoc,rep:7)
     * UBSan: signed integer overflow: 33965809752105870 * 368596309 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:484,execs:304,op:havoc,rep:3)
     * UBSan: signed integer overflow: 2 * 1249946282 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:2230,execs:1381,op:havoc,rep:7)
     */
    return (long long)n * (n + 1) * (2 * n + 1) / 6;
}

int main(void) {
    int n;
    long long result;
    
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 1) {
        printf("Please enter a positive integer\n");
        return EXIT_FAILURE;
    }
    
    result = sum_of_squares(n);
    printf("Sum of squares from 1 to %d is %lld\n", n, result);
    
    return EXIT_SUCCESS;
}