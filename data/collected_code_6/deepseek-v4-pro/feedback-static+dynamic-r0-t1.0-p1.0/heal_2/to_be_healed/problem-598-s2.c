#include <stdio.h>

int int_pow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        /* Possible weaknesses found:
         * UBSan: division by zero (AFL crash: id:000001,sig:06,src:000001,time:951,execs:665,op:havoc,rep:3)
         */
        if (result > 2147483647 / base) {
            return -1;
        }
        result *= base;
    }
    return result;
}

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
         * ASan: FPE (AFL crash: id:000001,sig:06,src:000001,time:951,execs:665,op:havoc,rep:3)
         */
        int power = int_pow(remainder, digits);
        if (power < 0) {
            return 0;
        }
        if (sum > 2147483647 - power) {
            return 0;
        }
        sum += power;
        temp /= 10;
    }

    return sum == original;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:631,execs:454,op:flip2,pos:2; likely memory-safety defect
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