#include <stdio.h>

int sum_positive_series(int n) {
    int sum = 0;
    int term = n;
    
    while (term > 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1935130545 + 215014495 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:210,execs:126,op:havoc,rep:5)
         */
        sum += term;
        term -= 2;
    }
    
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    
    int result = sum_positive_series(n);
    printf("Sum of series: %d\n", result);
    
    return 0;
}