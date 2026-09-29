#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

int countDigits(int n) {
    int count = 0;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}

bool isArmstrong(int num) {
    int n = 0, result = 0, temp = num;

    while (temp != 0) {
        n++;
        temp /= 10;
    }

    temp = num;
    while (temp != 0) {
        int remainder = temp % 10;
        long long powerResult = 1;
        for (int i = 0; i < n; i++) {
            /* Possible weaknesses found:
             * ASan: FPE (AFL crash: id:000001,sig:06,src:000001,time:160,execs:78,op:arith8,pos:1,val:-5)
             * UBSan: division by zero (AFL crash: id:000001,sig:06,src:000001,time:160,execs:78,op:arith8,pos:1,val:-5)
             */
            if (LLONG_MAX / remainder < powerResult) {
                return false;
            }
            powerResult *= remainder;
        }
        if (result > LLONG_MAX - powerResult) {
            return false;
        }
        result += powerResult;
        temp /= 10;
    }

    return (result == num);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:8,execs:15,op:(null),pos:0; likely memory-safety defect
  */

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