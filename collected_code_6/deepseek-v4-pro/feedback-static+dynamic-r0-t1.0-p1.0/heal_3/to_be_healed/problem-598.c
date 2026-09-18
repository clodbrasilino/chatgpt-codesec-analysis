#include <stdio.h>

int int_pow(int base, int exp) {
    int result = 1;
    int i;
    for (i = 0; i < exp; i++) {
        if (result > 2147483647 / base) {
            return -1;
        }
        result *= base;
    }
    return result;
}

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
        int pow_result = int_pow(remainder, digits);
        if (pow_result == -1) {
            return 0;
        }
        if (result > 2147483647 - pow_result) {
            return 0;
        }
        result += pow_result;
        original /= 10;
    }

    return result == number;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:1304,execs:732,op:havoc,rep:5; likely memory-safety defect
  */

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