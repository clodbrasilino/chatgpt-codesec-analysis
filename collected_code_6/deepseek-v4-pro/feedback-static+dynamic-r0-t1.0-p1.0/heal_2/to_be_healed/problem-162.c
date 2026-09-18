#include <stdio.h>

int sum_positive_series(int n) {
    int sum = 0;
    
    if (n <= 0) {
        return 0;
    }
    
    for (int i = n; i > 0; i -= 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2133332320 + 66666602 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:191,execs:142,op:havoc,rep:4)
         */
        sum += i;
    }
    
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    int result = sum_positive_series(n);
    printf("Sum: %d\n", result);
    
    return 0;
}