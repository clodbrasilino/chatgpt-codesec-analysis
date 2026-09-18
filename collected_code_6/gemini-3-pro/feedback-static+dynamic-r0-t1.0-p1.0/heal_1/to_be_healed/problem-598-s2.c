#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isArmstrong(int num) {
    if (num < 0) {
        return 0;
    }

    int originalNum = num;
    int sum = 0;
    int digits = 0;

    int temp = num;
    while (temp != 0) {
        digits++;
        temp /= 10;
    }

    temp = num;
    while (temp != 0) {
        int remainder = temp % 10;
        /* Possible weaknesses found:
         * UBSan: 3.48678e+09 is outside the range of representable values of type 'int' (AFL crash: id:000001,sig:06,src:000001,time:793,execs:414,op:havoc,rep:6)
         * UBSan: signed integer overflow: 1085666722 + 1073741824 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:554,execs:299,op:havoc,rep:6)
         */
        sum += (int)pow(remainder, digits);
        temp /= 10;
    }

    return (sum == originalNum);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000001,time:1253,execs:633,op:havoc,rep:7; likely memory-safety defect
  */

int main() {
    int num;

    if (scanf("%d", &num) != 1) {
        return EXIT_FAILURE;
    }

    if (isArmstrong(num)) {
        printf("Armstrong\n");
    } else {
        printf("Not Armstrong\n");
    }

    return EXIT_SUCCESS;
}