#include <stdio.h>
#include <stdbool.h>

bool is_abundant(int num) {
    if (num < 1) {
        return false;
    }

    int sum = 0;
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2032816140 + 660865020 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:62177,execs:2259,op:havoc,rep:5)
             */
            sum += i;
        }
    }

    return sum > num;
}

int main(void) {
    int number;

    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (is_abundant(number)) {
        printf("%d is an abundant number\n", number);
    } else {
        printf("%d is not an abundant number\n", number);
    }

    return 0;
}