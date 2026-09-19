#include <stdio.h>
#include <math.h>

int countDigits(int n) {
    if (n == 0) return 1;
    int count = 0;
    while (n != 0) {
        n /= 10;
        ++count;
    }
    return count;
}

int isArmstrong(int number) {
    /* Possible weaknesses found:
     *  The scope of the variable 'remainder' can be reduced. [variableScope]
     */
    int result = 0, n = 0, remainder;
    for (int temp = number; temp != 0; temp /= 10) {
        ++n;
    }

    int originalNumber = number;
    while (originalNumber != 0) {
        remainder = originalNumber % 10;
        /* Possible weaknesses found:
         * UBSan: 3.48679e+09 is outside the range of representable values of type 'int'
         * UBSan: 2.17789e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:605,execs:479,op:havoc,rep:3)
         * UBSan: 3.48678e+09 is outside the range of representable values of type 'int' (AFL crash: id:000001,sig:06,src:000001,time:1103,execs:872,op:havoc,rep:3)
         */
        result += pow(remainder, n);
        originalNumber /= 10;
    }

    return result == number;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (isArmstrong(num)) {
        printf("%d is an Armstrong number.\n", num);
    } else {
        printf("%d is not an Armstrong number.\n", num);
    }

    return 0;
}