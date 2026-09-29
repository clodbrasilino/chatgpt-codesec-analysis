#include <stdio.h>
#include <math.h>

int sum_of_digits(long long num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int main() {
    int base, power;
    printf("Enter the base: ");
    if (scanf("%d", &base) != 1) {
        return 1;
    }
    printf("Enter the power: ");
    if (scanf("%d", &power) != 1) {
        return 1;
    }

    /* Possible weaknesses found:
     * UBSan: inf is outside the range of representable values of type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:636,execs:239,op:havoc,rep:3)
     */
    long long result = pow(base, power);
    int sum = sum_of_digits(result);
    printf("Sum of digits of %lld is: %d\n", result, sum);
    return 0;
}