#include <stdio.h>
#include <stdbool.h>

int reverseNumber(int num) {
    int reversed = 0;
    while (num > 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 484177494 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:1106,execs:455,op:quick,pos:11)
         */
        reversed = (reversed * 10) + (num % 10);
        num /= 10;
    }
    return reversed;
}

bool checkCondition(int num) {
    int reversed = reverseNumber(num);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 2140000341 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:4852,execs:1836,op:havoc,rep:2)
     */
    return (2 * reversed - 1) == num;
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