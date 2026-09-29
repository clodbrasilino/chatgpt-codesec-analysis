#include <stdio.h>

int find_parity(int num) {
    int parity = 0;
    while (num) {
        parity ^= 1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -2147483648 - 1 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:678,execs:313,op:havoc,rep:4)
         */
        num &= (num - 1);
    }
    return parity;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    int result = find_parity(number);
    if (result == 0) {
        printf("Even parity\n");
    } else {
        printf("Odd parity\n");
    }
    return 0;
}