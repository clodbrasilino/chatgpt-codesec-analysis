#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int reverseNumber(int num) {
    int reversed = 0;
    while (num > 0) {
        if (reversed > INT_MAX / 10 || (reversed == INT_MAX / 10 && num % 10 > INT_MAX % 10)) {
            return 0;
        }
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
     * UBSan: signed integer overflow: 2 * 1111111111 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:5931,execs:2553,op:havoc,rep:14)
     * UBSan: signed integer overflow: 2 * 1638839751 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:2188,execs:961,op:havoc,rep:4)
     */
    if ((2 * reversed) > INT_MAX || (2 * reversed - 1) != num) {
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