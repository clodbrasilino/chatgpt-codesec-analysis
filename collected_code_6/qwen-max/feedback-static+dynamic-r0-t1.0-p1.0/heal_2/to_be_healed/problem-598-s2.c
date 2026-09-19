#include <stdio.h>
#include <math.h>

int countDigits(int n) {
    int count = 0;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}

int isArmstrong(int num) {
    /* Possible weaknesses found:
     *  The scope of the variable 'remainder' can be reduced. [variableScope]
     */
    int n = 0, result = 0, remainder;
    for (int originalNum = num; originalNum != 0; originalNum /= 10) {
        n++;
    }

    for (int originalNum = num; originalNum != 0; originalNum /= 10) {
        remainder = originalNum % 10;
        /* Possible weaknesses found:
         * UBSan: 3.48679e+09 is outside the range of representable values of type 'int'
         * UBSan: 3.48783e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1243,execs:1169,op:havoc,rep:8)
         * UBSan: 3.48678e+09 is outside the range of representable values of type 'int' (AFL crash: id:000001,sig:06,src:000001,time:2577,execs:2375,op:havoc,rep:10)
         */
        result += pow(remainder, n);
    }

    return (result == num);
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    if (isArmstrong(number)) {
        printf("%d is an Armstrong number.\n", number);
    } else {
        printf("%d is not an Armstrong number.\n", number);
    }

    return 0;
}