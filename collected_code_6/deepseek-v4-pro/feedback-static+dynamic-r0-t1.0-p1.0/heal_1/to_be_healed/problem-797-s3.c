#include <stdio.h>

int sum_of_odd_numbers(int l, int r) {
    if (l > r) {
        return 0;
    }

    if (l % 2 == 0) {
        l++;
    }
    if (r % 2 == 0) {
        r--;
    }

    if (l > r) {
        return 0;
    }

    int n = (r - l) / 2 + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 276084 * 552276 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:596,execs:405,op:havoc,rep:8)
     * UBSan: signed integer overflow: 111114 * 222232 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:873,execs:572,op:havoc,rep:3)
     */
    return n * (l + r) / 2;
}

int main(void) {
    int l, r;
    printf("Enter the range l and r: ");
    if (scanf("%d %d", &l, &r) != 2) {
        printf("Invalid input\n");
        return 1;
    }

    int result = sum_of_odd_numbers(l, r);
    printf("Sum of odd numbers in range [%d, %d] = %d\n", l, r, result);

    return 0;
}