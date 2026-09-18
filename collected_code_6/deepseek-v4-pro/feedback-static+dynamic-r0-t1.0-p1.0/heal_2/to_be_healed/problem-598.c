#include <stdio.h>
#include <math.h>

int is_armstrong(int number) {
    int original;
    int result = 0;
    int digits = 0;

    if (number < 0) {
        return 0;
    }

    original = number;

    while (original != 0) {
        original /= 10;
        digits++;
    }

    original = number;

    while (original != 0) {
        int remainder = original % 10;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1417790874 + 1073741824 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:867,execs:559,op:havoc,rep:12)
         * UBSan: signed integer overflow: -2147483647 + -2147483648 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:536,execs:355,op:havoc,rep:9)
         * UBSan: 3.48678e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:531,execs:353,op:havoc,rep:11)
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