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
    int originalNum, remainder, n = 0, result = 0;
    /* Possible weaknesses found:
     *  Value stored to 'originalNum' is never read [deadcode.DeadStores]
     *  originalNum is assigned
     */
    originalNum = num;

    /* Possible weaknesses found:
     *  Variable 'originalNum' is reassigned a value before the old one has been used. [redundantAssignment]
     *  originalNum is overwritten
     */
    for (originalNum = num; originalNum != 0; originalNum /= 10) {
        n++;
    }

    originalNum = num;
    while (originalNum != 0) {
        remainder = originalNum % 10;
        /* Possible weaknesses found:
         * UBSan: 2.17789e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:2885,execs:1218,op:havoc,rep:2)
         * UBSan: 3.48678e+09 is outside the range of representable values of type 'int' (AFL crash: id:000001,sig:06,src:000005,time:8334,execs:3525,op:havoc,rep:3)
         */
        result += pow(remainder, n);
        originalNum /= 10;
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