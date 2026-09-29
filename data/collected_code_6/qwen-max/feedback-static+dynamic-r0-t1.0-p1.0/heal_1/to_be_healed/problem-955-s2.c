#include <stdio.h>
#include <stdbool.h>

bool is_abundant(int num) {
    int sum = 1;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            sum += i;
            if (i != num / i) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 2143881412 + 10899668 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:3484,execs:1538,op:havoc,rep:1)
                 */
                sum += num / i;
            }
        }
    }
    return sum > num;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (is_abundant(number)) {
        printf("%d is an abundant number.\n", number);
    } else {
        printf("%d is not an abundant number.\n", number);
    }

    return 0;
}