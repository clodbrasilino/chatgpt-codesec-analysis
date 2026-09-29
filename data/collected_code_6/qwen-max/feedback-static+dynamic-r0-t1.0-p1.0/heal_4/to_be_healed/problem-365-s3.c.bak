#include <stdio.h>

int count_digits(long num) {
    int count = 0;
    if (num == 0) return 1;
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000009,time:17566,execs:6675,op:havoc,rep:1)
     */
    if (num < 0) num = -num;
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
        printf("Invalid input.\n");
        return 1;
    }
    int result = count_digits(number);
    if (result == 0) {
        printf("No digits found.\n");
    } else {
        printf("Number of digits: %d\n", result);
    }
    return 0;
}