#include <stdio.h>

int reverse_number(int num) {
    int reversed = 0;
    while (num > 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 629462729 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000006,time:2047,execs:810,op:havoc,rep:2)
         */
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return reversed;
}

int is_one_less_than_twice_reverse(int n) {
    int reversed = reverse_number(n);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 1194316131 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:27918,execs:11003,op:havoc,rep:59)
     * UBSan: signed integer overflow: 2 * 1999659995 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000006,time:2047,execs:810,op:havoc,rep:2)
     */
    return (2 * reversed - 1 == n);
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    if (is_one_less_than_twice_reverse(number)) {
        printf("The number is one less than twice its reverse.\n");
    } else {
        printf("The number is not one less than twice its reverse.\n");
    }
    return 0;
}