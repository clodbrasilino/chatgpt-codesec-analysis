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
         * UBSan: signed integer overflow: -1285418553 - 911111122 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:21831,execs:8136,op:havoc,rep:19)
         * UBSan: signed integer overflow: 911111122 + 2098437621 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:21831,execs:8136,op:havoc,rep:19)
         */
        if (number + (multiple - remainder) > INT_MAX || number + (multiple - remainder) < INT_MIN) {
            return 0;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -1285418553 - 911111122 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:21831,execs:8136,op:havoc,rep:19)
         * UBSan: signed integer overflow: 911111122 + 2098437621 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:21831,execs:8136,op:havoc,rep:19)
         */
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