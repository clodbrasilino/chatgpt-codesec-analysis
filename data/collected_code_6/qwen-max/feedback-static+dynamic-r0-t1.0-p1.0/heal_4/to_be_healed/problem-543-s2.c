#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

void addAndPrintDigits(long a, long b) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 99 + 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000004,time:587,execs:657,op:havoc,rep:3)
     */
    long sum = a + b;
    if (sum < LONG_MIN || sum > LONG_MAX) {
        printf("Sum: Overflow, Number of Digits: N/A\n");
        return;
    }
    int digits = (sum == 0) ? 1 : (int) log10(labs(sum)) + 1;
    printf("Sum: %ld, Number of Digits: %d\n", sum, digits);
}

int main() {
    long num1, num2;

    printf("Enter first number: ");
    if (scanf("%ld", &num1) != 1) return 1;

    printf("Enter second number: ");
    if (scanf("%ld", &num2) != 1) return 2;

    addAndPrintDigits(num1, num2);

    return 0;
}