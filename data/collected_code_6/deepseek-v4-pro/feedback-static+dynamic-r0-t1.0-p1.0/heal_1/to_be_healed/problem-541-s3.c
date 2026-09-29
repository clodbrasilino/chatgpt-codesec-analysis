#include <stdio.h>

int is_abundant(int n) {
    if (n <= 1) return 0;

    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 2145400588 + 8370851 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:4654,execs:2303,op:havoc,rep:2)
                 */
                sum += n / i;
            }
        }
    }
    return sum > n;
}

int main(void) {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (is_abundant(num)) {
        printf("%d is an abundant number\n", num);
    } else {
        printf("%d is not an abundant number\n", num);
    }

    return 0;
}