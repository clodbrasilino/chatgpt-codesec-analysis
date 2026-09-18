#include <stdio.h>
#include <stdlib.h>

int sum_of_proper_divisors(int n) {
    int sum = 1;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 1735953100 + 520785927 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000017,time:39337,execs:15861,op:havoc,rep:15)
                 * UBSan: signed integer overflow: 1943055578 + 222063492 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:21650,execs:8506,op:havoc,rep:10)
                 */
                sum += n / i;
            }
        }
    }
    return sum;
}

int is_abundant(int number) {
    if (number < 12) {
        return 0;
    }
    return sum_of_proper_divisors(number) > number;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (is_abundant(num)) {
        printf("%d is an abundant number.\n", num);
    } else {
        printf("%d is not an abundant number.\n", num);
    }
    return 0;
}