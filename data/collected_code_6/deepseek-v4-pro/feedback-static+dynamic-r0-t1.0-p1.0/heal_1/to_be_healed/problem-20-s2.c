#include <stdio.h>

int is_woodall(int n) {
    if (n <= 0) return 0;
    
    int m = 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 27 * 134217728 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:2541,execs:1194,op:havoc,rep:4)
     * UBSan: signed integer overflow: -2147483648 - 1 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:2541,execs:1194,op:havoc,rep:4)
     */
    while (m * (1 << m) - 1 <= n) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 27 * 134217728 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:2541,execs:1194,op:havoc,rep:4)
         */
        if (m * (1 << m) - 1 == n) return 1;
        m++;
    }
    
    return 0;
}

int main(void) {
    int num;
    
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (is_woodall(num)) {
        printf("%d is a Woodall number\n", num);
    } else {
        printf("%d is not a Woodall number\n", num);
    }
    
    return 0;
}