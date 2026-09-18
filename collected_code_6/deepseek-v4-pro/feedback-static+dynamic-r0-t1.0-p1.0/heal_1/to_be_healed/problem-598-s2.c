#include <stdio.h>
#include <math.h>

int is_armstrong(int num) {
    int original = num;
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
         * UBSan: 3.48678e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1614,execs:795,op:havoc,rep:12)
         * UBSan: signed integer overflow: 1357266674 + 1073741824 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:2360,execs:1166,op:havoc,rep:11)
         */
        sum += (int)pow(remainder, digits);
        temp /= 10;
    }

    return sum == original;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000001,time:2051,execs:1015,op:havoc,rep:12; likely memory-safety defect
  */

int main(void) {
    int number;

    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (number < 0) {
        printf("Please enter a non-negative number\n");
        return 1;
    }

    if (is_armstrong(number)) {
        printf("%d is an Armstrong number\n", number);
    } else {
        printf("%d is not an Armstrong number\n", number);
    }

    return 0;
}