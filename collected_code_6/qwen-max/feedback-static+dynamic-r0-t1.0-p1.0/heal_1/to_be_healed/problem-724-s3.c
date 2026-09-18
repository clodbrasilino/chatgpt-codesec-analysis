#include <stdio.h>
#include <stdlib.h>
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
    int base, exp;
    printf("Enter base and exponent: ");
    if (scanf("%d %d", &base, &exp) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * UBSan: 2.96428e+79 is outside the range of representable values of type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:537,execs:227,op:havoc,rep:3)
     */
    long long result = pow(base, exp);
    int sum = sum_of_digits(result);
    printf("Sum of digits: %d\n", sum);

    return EXIT_SUCCESS;
}