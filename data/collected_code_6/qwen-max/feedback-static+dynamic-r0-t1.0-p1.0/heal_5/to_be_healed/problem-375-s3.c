#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int round_to_nearest_multiple(int number, int multiple) {
    if (multiple == 0) {
        return 0;
    }
    int remainder = number % multiple;
    if (remainder < abs(multiple) / 2) {
        if (number - remainder > INT_MAX || number - remainder < INT_MIN) {
            return 0;
        }
        return number - remainder;
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2147483647 - -1 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:1331,execs:521,op:havoc,rep:1)
         * UBSan: signed integer overflow: -2147483648 - 1 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:210,execs:96,op:havoc,rep:3)
         * UBSan: signed integer overflow: 2147483647 + 1 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:210,execs:96,op:havoc,rep:3)
         */
        if (INT_MAX - multiple + 1 < remainder || INT_MIN - multiple + 1 > -remainder) {
            return 0;
        }
        if ((number > 0 && INT_MAX - (multiple - remainder) < number) || 
            (number < 0 && INT_MIN + (multiple - remainder) > number)) {
            return 0;
        }
        return number + (multiple - remainder);
    }
}

int main() {
    int number, multiple;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        return 1;
    }
    printf("Enter the multiple: ");
    if (scanf("%d", &multiple) != 1) {
        return 1;
    }
    int result = round_to_nearest_multiple(number, multiple);
    printf("Rounded number: %d\n", result);
    return 0;
}