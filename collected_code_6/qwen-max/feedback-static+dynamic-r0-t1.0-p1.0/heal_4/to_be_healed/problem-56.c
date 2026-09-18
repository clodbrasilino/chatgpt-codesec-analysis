#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int reverseNumber(int num) {
    int reversed = 0;
    while (num != 0) {
        if (reversed > INT_MAX / 10 || (reversed == INT_MAX / 10 && num % 10 > 7)) {
            return 0;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -361228441 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:591,execs:272,op:havoc,rep:2)
         */
        reversed = (reversed * 10) + (num % 10);
        num /= 10;
    }
    return reversed;
}

bool checkCondition(int num) {
    int reversed = reverseNumber(num);
    if (reversed == 0) {
        return false;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * -1192340711 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:2072,execs:898,op:havoc,rep:2)
     */
    if (INT_MAX / 2 < reversed || (2 * reversed - 1) != num) {
        return false;
    }
    return true;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    if (checkCondition(number)) {
        printf("The number is one less than twice its reverse.\n");
    } else {
        printf("The number is not one less than twice its reverse.\n");
    }

    return 0;
}