#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int isArmstrong(int num) {
    if (num < 0) {
        return 0;
    }

    int originalNum = num;
    /* Possible weaknesses found:
     *  The scope of the variable 'remainder' can be reduced. [variableScope]
     *  Variable 'remainder' is assigned a value that is never used. [unreadVariable]
     */
    int remainder = 0;
    int result = 0;
    int n = 0;

    int temp = num;
    while (temp != 0) {
        temp /= 10;
        ++n;
    }

    temp = num;
    while (temp != 0) {
        remainder = temp % 10;
        /* Possible weaknesses found:
         * UBSan: 3.48678e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1093,execs:554,op:havoc,rep:2)
         * UBSan: 3.76926e+09 is outside the range of representable values of type 'int' (AFL crash: id:000001,sig:06,src:000001,time:1653,execs:822,op:havoc,rep:2)
         */
        result += pow(remainder, n);
        temp /= 10;
    }

    if (result == originalNum) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    int num;
    int scanResult = scanf("%d", &num);

    if (scanResult != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (isArmstrong(num)) {
        printf("%d is an Armstrong number.\n", num);
    } else {
        printf("%d is not an Armstrong number.\n", num);
    }

    return EXIT_SUCCESS;
}