#include <stdio.h>
#include <stdlib.h>

int count_digits(long num) {
    if (num == 0) return 1;
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000009,time:7337,execs:6740,op:havoc,rep:3)
     */
    if (num < 0) num = -num;
    int count = 0;
    while (num > 0) {
        num /= 10;
        count++;
    }
    return count;
}

int main() {
    long number;
    printf("Enter a number: ");
    if (scanf("%ld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Number of digits: %d\n", count_digits(number));
    return 0;
}