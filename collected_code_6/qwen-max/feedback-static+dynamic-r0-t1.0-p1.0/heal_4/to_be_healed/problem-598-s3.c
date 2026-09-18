#include <stdio.h>
#include <math.h>
#include <limits.h>

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
    int result = 0, n = 0, originalNumber = number, remainder;

    while (originalNumber != 0) {
        ++n;
        originalNumber /= 10;
    }

    originalNumber = number;
    while (originalNumber != 0) {
        remainder = originalNumber % 10;
        if (remainder > 0 && INT_MAX / pow(remainder, n-1) < remainder) {
            return 0;
        }
        long long temp = 1;
        for (int i = 0; i < n; ++i) {
            if (temp > INT_MAX / remainder) {
                return 0;
            }
            temp *= remainder;
        }
        result += temp;
        originalNumber /= 10;
    }

    return result == number;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:8,execs:15,op:(null),pos:0; likely memory-safety defect
  */

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