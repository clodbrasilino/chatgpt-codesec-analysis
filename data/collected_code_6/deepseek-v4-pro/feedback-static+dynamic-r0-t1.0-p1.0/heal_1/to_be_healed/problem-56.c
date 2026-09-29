#include <stdio.h>
#include <stdbool.h>

int reverse_number(int n) {
    int rev = 0;
    while (n != 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 924127160 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:897,execs:403,op:havoc,rep:1)
         */
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return rev;
}

bool is_one_less_than_twice_reverse(int n) {
    int rev = reverse_number(n);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 1832750811 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000006,time:3899,execs:1728,op:havoc,rep:2)
     */
    return n == (2 * rev - 1);
}

int main(void) {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    
    if (is_one_less_than_twice_reverse(num)) {
        printf("%d is one less than twice its reverse.\n", num);
    } else {
        printf("%d is not one less than twice its reverse.\n", num);
    }
    
    return 0;
}