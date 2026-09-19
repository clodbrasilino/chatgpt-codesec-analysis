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
    if (num < 0) return false;
    int n = countDigits(num);
    int result = 0;
    int temp = num;

    for (; temp; temp /= 10) {
        int remainder = temp % 10;
        uint64_t powerResult = 1;
        for (int i = 0; i < n; ++i) {
            if (remainder == 0 || UINT64_MAX / remainder < powerResult) {
                return false;
            }
            powerResult *= remainder;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2147483647 - -808182895 cannot be represented in type 'int'
         * UBSan: signed integer overflow: 2147483647 - -808182895 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1671,execs:633,op:havoc,rep:3)
         */
        if (result > INT_MAX - (int)powerResult) {
            return false;
        }
        result += powerResult;
    }

    return (result == num);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000001,time:4274,execs:1616,op:havoc,rep:4; likely memory-safety defect
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