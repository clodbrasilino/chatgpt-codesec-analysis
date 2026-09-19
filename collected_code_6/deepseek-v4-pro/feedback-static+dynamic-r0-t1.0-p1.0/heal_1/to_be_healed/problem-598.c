#include <stdio.h>
#include <math.h>

int is_armstrong(int number) {
    int original = number;
    /* Possible weaknesses found:
     *  The scope of the variable 'remainder' can be reduced. [variableScope]
     */
    int remainder;
    int result = 0;
    int digits = 0;

    if (number < 0) {
        return 0;
    }

    while (original != 0) {
        original /= 10;
        digits++;
    }

    original = number;

    while (original != 0) {
        remainder = original % 10;
        /* Possible weaknesses found:
         * UBSan: 3.48678e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1475,execs:730,op:havoc,rep:1)
         * UBSan: signed integer overflow: 1073741825 + 1073741824 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:1488,execs:736,op:havoc,rep:2)
         * UBSan: signed integer overflow: -2137657950 + -2147483648 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:9718,execs:4734,op:havoc,rep:2)
         */
        result += (int)pow(remainder, digits);
        original /= 10;
    }

    return result == number;
}

int main() {
    int num;

    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (is_armstrong(num)) {
        printf("%d is an Armstrong number\n", num);
    } else {
        printf("%d is not an Armstrong number\n", num);
    }

    return 0;
}