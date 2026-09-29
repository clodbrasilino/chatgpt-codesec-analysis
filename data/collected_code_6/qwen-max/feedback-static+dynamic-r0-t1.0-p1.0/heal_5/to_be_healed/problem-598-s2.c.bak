#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>

int countDigits(int n) {
    int count = 0;
    if (n == 0) return 1;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}

bool isArmstrong(int num) {
    int n = countDigits(num);
    int result = 0;
    /* Possible weaknesses found:
     *  temp is initialized
     */
    int temp = num;

    if (num < 0) return false;

    /* Possible weaknesses found:
     *  temp is overwritten
     *  Redundant initialization for 'temp'. The initialized value is overwritten before it is read. [redundantInitialization]
     */
    for (temp = num; temp; temp /= 10) {
        int remainder = temp % 10;
        uint64_t powerResult = 1;
        for (int i = 0; i < n; ++i) {
            /* Possible weaknesses found:
             * UBSan: division by zero (AFL crash: id:000001,sig:06,src:000001,time:162,execs:78,op:arith8,pos:1,val:-5)
             */
            if (UINT64_MAX / remainder < powerResult) {
                return false;
            }
            powerResult *= remainder;
        }
        if (result > INT_MAX - powerResult) {
            return false;
        }
        result += powerResult;
    }

    return (result == num);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:7,execs:15,op:(null),pos:0; likely memory-safety defect
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