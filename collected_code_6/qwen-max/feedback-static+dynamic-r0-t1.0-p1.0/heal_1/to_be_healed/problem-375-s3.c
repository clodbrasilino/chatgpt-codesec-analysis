#include <stdio.h>
#include <stdlib.h>

int round_to_nearest_multiple(int number, int multiple) {
    if (multiple == 0) {
        return 0;
    }
    int remainder = number % multiple;
    if (remainder < abs(multiple) / 2) {
        return number - remainder;
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1652026823 + 810193920 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000005,time:13112,execs:6019,op:havoc,rep:1)
         * UBSan: signed integer overflow: -1832746553 - 1652026823 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000005,time:13112,execs:6019,op:havoc,rep:1)
         */
        return number + (multiple - remainder);
    }
}

int main() {
    int number, multiple;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        return 1;
    }
    printf("Enter the multiple: ");
    if (scanf("%d", &multiple) != 1) {
        return 1;
    }
    int result = round_to_nearest_multiple(number, multiple);
    printf("Rounded number: %d\n", result);
    return 0;
}