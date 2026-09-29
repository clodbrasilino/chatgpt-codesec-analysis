#include <stdio.h>
#include <math.h>

int count_digits(int num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

int is_armstrong(int num) {
    int original_num = num, sum = 0, digits = count_digits(num);
    while (num > 0) {
        int digit = num % 10;
        /* Possible weaknesses found:
         * UBSan: 2.43002e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1179,execs:408,op:havoc,rep:2)
         * UBSan: 3.48678e+09 is outside the range of representable values of type 'int' (AFL crash: id:000001,sig:06,src:000001,time:4177,execs:1609,op:havoc,rep:4)
         */
        sum += pow(digit, digits);
        num /= 10;
    }
    return sum == original_num;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    if (is_armstrong(number)) {
        printf("%d is an Armstrong number.\n", number);
    } else {
        printf("%d is not an Armstrong number.\n", number);
    }
    return 0;
}