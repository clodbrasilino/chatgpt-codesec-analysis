#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>

int highest_power_of_2_less_than_n(int n) {
    if (n <= 0) return 0;
    int power = 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1073741824 * 2 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:11413,execs:3768,op:havoc,rep:11)
     */
    while (power * 2 <= n && (uint64_t)power * 2 < (uint64_t)INT_MAX) {
        power *= 2;
    }
    return power;
}

int main() {
    int n;
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input. Please enter an integer.\n");
        return 1;
    }

    if (n > 0) {
        int result = highest_power_of_2_less_than_n(n);
        printf("The highest power of 2 less than or equal to %d is %d\n", n, result);
    } else {
        printf("Please enter a positive number.\n");
    }
    return 0;
}